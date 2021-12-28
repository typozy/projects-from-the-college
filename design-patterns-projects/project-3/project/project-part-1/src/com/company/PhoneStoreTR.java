package com.company;

public class PhoneStoreTR extends PhoneStore{
    private static int serialTR = 0;
    protected Phone createPhone(String model) {
        Phone phone = null;
        PhoneComponentFactory factory =
                new PhoneComponentFactoryTR();
        if (model.equals("maxEffort")) {
            phone = new PhoneMaximumEffort(factory);
            phone.setName("maxEffortTR"+Integer.toString(serialTR));
            ++serialTR;
        } else if (model.equals("iflasDeluxe")) {
            phone = new PhoneIflasDeluxe(factory);
            phone.setName("iflasDeluxeTR"+Integer.toString(serialTR));
            ++serialTR;
        } else if (model.equals("amanIflas")) {
            phone = new PhoneIIAmanIflas(factory);
            phone.setName("amanIflasTR"+Integer.toString(serialTR));
            ++serialTR;
        }
        return phone;
    }
}
