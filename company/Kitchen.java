package com.company;

import java.util.concurrent.Semaphore;

public class Kitchen {
    private final Semaphore semaphore = new Semaphore(4);

    public void goIn(){
        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void leave(){
            semaphore.release();
    }
}
