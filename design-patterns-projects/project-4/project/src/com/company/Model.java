package com.company;

import java.awt.*;
import java.util.ArrayList;

public class Model implements ModelInterface {

    private Bulk bulk;
    private int speed;
    private int simSpd;
    private int peopleCount;
    private int ventilatorCount;
    private int dieTime;
    private int timePassed;
    private double mortalityRate;
    private double spreadFactor;
    private Thread thread;
    ArrayList paintObservers;
    ArrayList countObservers;

    public Model() {
        paintObservers = new ArrayList();
        countObservers = new ArrayList();
    }

    public Model(Controller controller, View view) {
        paintObservers = new ArrayList();
        countObservers = new ArrayList();
    }

    public void start(int peopleCount, int speed, double mortalityRate, double spreadFactor, int simSpd) throws InterruptedException {
        this.speed = speed;
        this.mortalityRate = mortalityRate;
        this.dieTime = Math.round((float) (100.0 * (1.0 - mortalityRate)));
        this.simSpd = simSpd;
        this.peopleCount = peopleCount;
        this.ventilatorCount = Math.round((float) (peopleCount / 100.0));
        this.spreadFactor = spreadFactor;
        this.timePassed = 0;
        bulk = new Bulk();
        PersonFactory factory = new PersonFactory();
        if (peopleCount > 0)
            bulk.add(factory.createInfectedPerson(speed, dieTime));
        for (int i = 0; i < peopleCount - 1; i++) {
            bulk.add(factory.createHealthyPerson(speed));
        }
        thread = new Thread(this::run);
        thread.start();
    }

    public void pause() {
        thread.suspend();
    }

    public void play() {
        thread.resume();
    }

    public void stop() {
        thread.stop();
    }

    public void run() {
        while (true) {
            if (timePassed > 0) {
                for (int i = 0; i < bulk.getCount(); i++) {
                    Paintable person = bulk.getPerson(i);
                    if (person instanceof HealthyPerson) {
                        HealthyPerson healthy = (HealthyPerson) person;
                        if (healthy.inCollision()) {
                            healthy.decreaseRemainingTime();
                            if (healthy.remainingTime() == 0) {
                                healthy.stopCollision();
                                healthy.randomize();
                            }
                        } else {
                            healthy.move();
                        }
                    } else if (person instanceof InfectingPerson) {
                        InfectingPerson infecting = (InfectingPerson) person;
                        infecting.decreaseRemainingTime();
                        if (infecting.remainingTime() == 0) {
                            bulk.infectPerson(i, dieTime);
                        }
                    }
                }
                for (int i = 0; i < bulk.getCount(); i++) {
                    Paintable person = bulk.getPerson(i);
                    if (person instanceof PersonUseVentilator) {
                        PersonUseVentilator ventilator = (PersonUseVentilator) person;
                        ventilator.decreaseRemainingTime();
                        if (ventilator.remainingTime() == 0) {
                            bulk.giveHealth(i, speed);
                            ventilatorCount++;
                        }
                    }
                }
                for (int i = 0; i < bulk.getCount(); i++) {
                    Paintable person = bulk.getPerson(i);
                    if (person instanceof PersonInHospital) {
                        PersonInHospital ill = (PersonInHospital) person;
                        ill.decreaseTime();
                        if (ill.dieTime() == 0) {
                            bulk.diePersonInHospital(i);
                        } else if (ventilatorCount > 0) {
                            bulk.giveVentilatorToPatient(i, speed);
                            ventilatorCount--;
                        }
                    }
                }
                for (int i = 0; i < bulk.getCount(); i++) {
                    Paintable person = bulk.getPerson(i);
                    if (person instanceof InfectedPerson) {
                        InfectedPerson infected = (InfectedPerson) person;
                        infected.decreaseTime();
                        if (infected.dieTime() == 0) {
                            bulk.dieInfectedPerson(i);
                        } else if (infected.hospitalTime() == 0) {
                            if (ventilatorCount > 0) {
                                bulk.giveVentilatorToInfected(i, speed);
                                ventilatorCount--;
                            } else {
                                bulk.hospitalize(i, speed, infected.dieTime());
                            }
                        } else if (infected.inCollision()) {
                            infected.decreaseRemainingTime();
                            if (infected.remainingTime() == 0) {
                                infected.stopCollision();
                                infected.randomize();
                            }
                        } else {
                            infected.move();
                        }
                    }
                }
            }
            for (int i = 0; i < bulk.getCount() - 1; i++) {
                for (int j = i + 1; j < bulk.getCount(); j++) {
                    Paintable personI = bulk.getPerson(i);
                    Paintable personJ = bulk.getPerson(j);
                    if ((personI instanceof HealthyPerson || personI instanceof InfectedPerson) &&
                            (personJ instanceof HealthyPerson || personJ instanceof InfectedPerson)) {
                        if ((personI instanceof HealthyPerson && personJ instanceof InfectedPerson) ||
                                (personJ instanceof HealthyPerson && personI instanceof InfectedPerson)) {
                            HealthyPerson healthy;
                            int healthyIndex;
                            InfectedPerson infected;
                            int infectedIndex;
                            if (personI instanceof HealthyPerson) {
                                healthy = (HealthyPerson) personI;
                                healthyIndex = i;
                                infected = (InfectedPerson) personJ;
                                infectedIndex = j;
                            } else {
                                healthy = (HealthyPerson) personJ;
                                healthyIndex = j;
                                infected = (InfectedPerson) personI;
                                infectedIndex = i;
                            }
                            if (!healthy.inCollision() && !infected.inCollision() &&
                                    !(healthy.lastBumped() == infectedIndex && infected.lastBumped() == healthyIndex) &&
                                    Math.abs(healthy.getX() - infected.getX()) + Math.abs(healthy.getY() - infected.getY()) < 10) {
                                int die = Math.min(infected.dieTime(), infected.hospitalTime());
                                int coef = Math.max(healthy.coefficient(), infected.coefficient());
                                int rem = Math.min(die, coef);
                                if (rem > 0) {
                                    healthy.collide();
                                    infected.collide();
                                    healthy.setLastBumped(infectedIndex);
                                    infected.setLastBumped(healthyIndex);
                                    healthy.setRemainingTime(rem);
                                    infected.setRemainingTime(rem);
                                    int dist = Math.abs(healthy.getX() - infected.getX()) + Math.abs(healthy.getY() - infected.getY());
                                    double mask0 = healthy.maskRate();
                                    double mask1 = infected.maskRate();
                                    double prob = Math.min(spreadFactor * (1.0 + rem / 10.0) * mask0 * mask1 * (1.0 - dist / 10.0), 1.0);
                                    if (Math.random() < prob) {
                                        bulk.startInfection(healthyIndex, coef);
                                    }
                                }
                            }
                        } else if (personI instanceof HealthyPerson && personJ instanceof HealthyPerson) {
                            HealthyPerson healthy1 = (HealthyPerson) personI;
                            int healthy1index = i;
                            HealthyPerson healthy2 = (HealthyPerson) personJ;
                            int healthy2index = j;
                            if (!healthy1.inCollision() && !healthy2.inCollision() &&
                                    !(healthy1.lastBumped() == healthy2index && healthy2.lastBumped() == healthy1index) &&
                                    Math.abs(healthy1.getX() - healthy2.getX()) + Math.abs(healthy1.getY() - healthy2.getY()) < 10) {
                                healthy1.collide();
                                healthy2.collide();
                                healthy1.setLastBumped(healthy2index);
                                healthy2.setLastBumped(healthy1index);
                                int rem = Math.max(healthy1.coefficient(), healthy2.coefficient());
                                healthy1.setRemainingTime(rem);
                                healthy2.setRemainingTime(rem);
                            }
                        } else {
                            InfectedPerson infected1 = (InfectedPerson) personI;
                            int infected1index = i;
                            InfectedPerson infected2 = (InfectedPerson) personJ;
                            int infected2index = j;
                            if (!infected1.inCollision() && !infected2.inCollision() &&
                                    !(infected1.lastBumped() == infected2index && infected2.lastBumped() == infected1index) &&
                                    Math.abs(infected1.getX() - infected2.getX()) + Math.abs(infected1.getY() - infected2.getY()) < 10) {
                                int die1 = Math.min(infected1.dieTime(), infected1.hospitalTime());
                                int die2 = Math.min(infected1.dieTime(), infected1.hospitalTime());
                                int coef = Math.max(infected1.coefficient(), infected2.coefficient());
                                int rem = Math.min(Math.min(die1, die2), coef);
                                if (rem > 0) {
                                    infected1.collide();
                                    infected2.collide();
                                    infected1.setLastBumped(infected2index);
                                    infected2.setLastBumped(infected1index);
                                    infected1.setRemainingTime(rem);
                                    infected2.setRemainingTime(rem);
                                }
                            }
                        }
                    }
                }
            }
            ((View) paintObservers.get(0)).updatePaint();
            ((View) countObservers.get(0)).updateCount();
            timePassed++;
            try {
                Thread.sleep(1000 / simSpd);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public int getHealthy() {
        return bulk.getHealthy();
    }

    public int getInfecting() {
        return bulk.getInfecting();
    }

    public int getInfected() {
        return bulk.getInfected();
    }

    public int getHospitalized() {
        return bulk.getHospitalized();
    }

    public int getIntubated() {
        return bulk.getIntubated();
    }

    public int getDead() {
        return bulk.getDead();
    }

    public int getTotal() {
        return bulk.getCount();
    }

    public int getTime() {
        return timePassed;
    }

    public void paint(Graphics g) {
        bulk.paint(g);
    }

    public void registerCountObserver(View observer) {
        countObservers.add(observer);
    }

    public void removeCountObserver(View observer) {
        countObservers.remove(observer);
    }

    public void registerPaintObserver(View observer) {
        paintObservers.add(observer);
    }

    public void removePaintObserver(View observer) {
        paintObservers.remove(observer);
    }
}