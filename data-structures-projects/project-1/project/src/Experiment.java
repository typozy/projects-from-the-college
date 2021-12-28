
public class Experiment {

    private String expsetup;
    private String time;
    private int day;
    private float accuracy;
    private boolean isCompleted;

    public Experiment(){
        this("unknown","00.00",false,1,0.0f);
    }

    public Experiment(String setup, String tm, boolean iscmp, int d, float acc){
        expsetup = setup;
        time = tm;
        day = d;
        accuracy = acc;
        isCompleted = iscmp;
    }

    public int getDay() {
        return day;
    }

    public boolean completed() {
        return isCompleted;
    }

    public float getAccuracy(){
        return accuracy;
    }

    public void setAccuracy(float acc){
        accuracy = acc;
    }

    public Experiment clone(){
        Experiment temp = new Experiment();
        temp.expsetup = expsetup;
        temp.day = day;
        temp.time = time;
        temp.accuracy = accuracy;
        temp.isCompleted = isCompleted;
        return temp;
    }

    @Override
    public String toString() {
        return "Experiment{" +
                "setup='" + expsetup + '\'' +
                ", day=" + day +
                ", time='" + time + '\'' +
                ", accuracy=" + accuracy +
                ", completed=" + isCompleted +
                '}';
    }

}
