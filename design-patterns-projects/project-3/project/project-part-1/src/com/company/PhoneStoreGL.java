package com.company;

public class PhoneStoreGL extends PhoneStore{
    private static int serialGL = 0;
    protected Phone createPhone(String model) {
        Phone phone = null;
        PhoneComponentFactory factory =
                new PhoneComponentFactoryGL();
        if (model.equals("maxEffort")) {
            phone = new PhoneMaximumEffort(factory);
            phone.setName("maxEffortGL"+Integer.toString(serialGL));
            ++serialGL;
        } else if (model.equals("iflasDeluxe")) {
            phone = new PhoneIflasDeluxe(factory);
            phone.setName("iflasDeluxeGL"+Integer.toString(serialGL));
            ++serialGL;
        } else if (model.equals("amanIflas")) {
            phone = new PhoneIIAmanIflas(factory);
            phone.setName("amanIflasGL"+Integer.toString(serialGL));
            ++serialGL;
        }
        return phone;
    }
}
