package com.company;

import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;

public class Bulk implements Paintable {

    ArrayList people;
    public int count;
    public int healthyCount;
    public int infectingCount;
    public int infectedCount;
    public int patientCount;
    public int intubatedCount;
    public int deadCount;

    public Bulk() {
        people = new ArrayList();
        count = 0;
        healthyCount = 0;
        infectingCount = 0;
        infectedCount = 0;
        patientCount = 0;
        intubatedCount = 0;
        deadCount = 0;
    }

    public void add(Paintable person) {
        people.add(person);
        count++;
        if (person instanceof HealthyPerson)
            healthyCount++;
        else
            infectedCount++;
    }

    public void startInfection(int i, int time) {
        people.set(i, new InfectingPerson((HealthyPerson) people.get(i), time));
        healthyCount--;
        infectingCount++;
    }

    public void infectPerson(int i, int time) {
        people.set(i, new InfectedPerson((InfectingPerson) people.get(i), time));
        infectingCount--;
        infectedCount++;
    }

    public int getCount() {
        return count;
    }

    public Paintable getPerson(int index) {
        return (Paintable) people.get(index);
    }

    public void hospitalize(int i, int speed, int dieTime) {
        people.set(i, new PersonInHospital((InfectedPerson) people.get(i)));
        infectedCount--;
        patientCount++;
    }

    public void giveHealth(int i, int speed) {
        people.set(i, new HealthyPerson((PersonUseVentilator) people.get(i)));
        intubatedCount--;
        healthyCount++;
    }

    public void giveVentilatorToInfected(int i, int speed) {
        people.set(i, new PersonUseVentilator((InfectedPerson) people.get(i)));
        infectedCount--;
        intubatedCount++;
    }

    public void giveVentilatorToPatient(int i, int speed) {
        people.set(i, new PersonUseVentilator((PersonInHospital) people.get(i)));
        patientCount--;
        intubatedCount++;
    }

    public void dieInfectedPerson(int i) {
        people.set(i, new DeadPerson());
        infectedCount--;
        deadCount++;
    }

    public void diePersonInHospital(int i) {
        people.set(i, new DeadPerson());
        patientCount--;
        deadCount++;
    }

    public int getHealthy() {
        return healthyCount;
    }

    public int getInfecting() {
        return infectingCount;
    }

    public int getInfected() {
        return infectedCount;
    }

    public int getHospitalized() {
        return patientCount;
    }

    public int getIntubated() {
        return intubatedCount;
    }

    public int getDead() {
        return deadCount;
    }

    @Override
    public void paint(Graphics g) {
        g.setColor(Color.GRAY);
        g.fillRect(0, 0, 1000, 600);
        Iterator iterator = people.iterator();
        while (iterator.hasNext()) {
            Paintable printable = (Paintable) iterator.next();
            printable.paint(g);
        }
    }
}
