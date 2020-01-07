package com.company;

import java.util.concurrent.Semaphore;

class IntCell {
    private int n = 0;
    public int getN() {return n;}
    public void setN(int n) {this.n = n;}
}
class Count extends Thread {
    private static IntCell n = new IntCell();
    private final static Semaphore available = new Semaphore(1, true);
    @Override public void run() {
        int temp;
        for (int i = 0; i < 200000; i++) {
            synchronized (n) {
                temp = n.getN();
                n.setN(temp + 1);
            }
           /* try {
                available.acquire();
                temp = n.getN();
                n.setN(temp + 1);
                available.release();

            } catch (InterruptedException e) {}*/

            }
        }


    public static void main(String[] args) {
        Count p = new Count();
        Count q = new Count();
        p.start();
        q.start();
        try { p.join(); q.join(); }
        catch (InterruptedException e) { }
        System.out.println("The value of n is " + n.getN());
       /* var kitchen = new Kitchen();
        var sticks = new Stick[]{new Stick(),new Stick(),new Stick(),new Stick(),new Stick()};
        for (int i = 0; i <5 ; i++) {
            new Philosopher(i, sticks, kitchen).start();
        }*/
    }

    public static void main2(String[] args) {

    }
}