package com.company;

public abstract class PhoneStore {
    protected abstract Phone createPhone(String model);
    public Phone orderPhone(String model){
        Phone phone = createPhone(model);
        phone.prepare();
        phone.insertCPUnRAM();
        phone.insertDisplay();
        phone.insertBattery();
        phone.insertStorage();
        phone.insertCamera();
        phone.coverCase();
        return phone;
    }
}
