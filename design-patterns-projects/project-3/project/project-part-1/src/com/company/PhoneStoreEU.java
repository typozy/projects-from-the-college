package com.company;

public class PhoneStoreEU extends PhoneStore{
    private static int serialEU = 0;
    protected Phone createPhone(String model) {
        Phone phone = null;
        PhoneComponentFactory factory =
                new PhoneComponentFactoryEU();
        if (model.equals("maxEffort")) {
            phone = new PhoneMaximumEffort(factory);
            phone.setName("maxEffortEU"+Integer.toString(serialEU));
            ++serialEU;
        } else if (model.equals("iflasDeluxe")) {
            phone = new PhoneIflasDeluxe(factory);
            phone.setName("iflasDeluxeEU"+Integer.toString(serialEU));
            ++serialEU;
        } else if (model.equals("amanIflas")) {
            phone = new PhoneIIAmanIflas(factory);
            phone.setName("amanIflasEU"+Integer.toString(serialEU));
            ++serialEU;
        }
        return phone;
    }
}
