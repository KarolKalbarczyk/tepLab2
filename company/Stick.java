package com.company;

import java.util.concurrent.Semaphore;

public class Stick {
    private final Semaphore semaphore = new Semaphore(1);

    public void get() {
        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void letGo(){
        semaphore.release();
    }

}
