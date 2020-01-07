package com.company;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Main {

    public static void main(String[] args) {
       /* var plus = new Account(100);
        var minus = new Account(-100);
        plus.start();
        minus.start();
        try { plus.join(); minus.join(); }
        catch (InterruptedException e){}
        System.out.println(Account.cash.getCash());*/
        printNumber();
    }

    public static void printNumber(){
        ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);
        executor.scheduleAtFixedRate(() -> System.out.print(666 + " "), 0, 1, TimeUnit.SECONDS);
    }
}

class Account extends Thread{
    static final Cash cash =new Cash();
    int change;

    public Account(int change) {
        this.change = change;
    }

    @Override
    public void run(){
        changeCash();
    }

    public void changeCash(){
        for (int i = 0; i <1000000 ; i++) {
            int temp;
            synchronized (cash) {
                temp = cash.getCash();
                cash.setCash(temp+change);
            }
        }
    }

}

class Cash{
    private int cash = 0;

    public int getCash() {
        return cash;
    }

    public void setCash(int cash) {
        this.cash = cash;
    }

}