package com.company;

public class Philosopher extends Thread {
    int number;
    Stick[] sticks;
    int position;
    Kitchen kitchen;

    public Philosopher(int number,Stick[] sticks,Kitchen kitchen) {
        super();
        this.kitchen = kitchen;
        this.number = number;
        this.sticks = sticks;
    }

    public void setPosition(int position){
        this.position = position;
    }

    @Override
    public void run() {
        kitchen.goIn();
        System.out.println("Philosopher nr " + number + "has entered kitchen");
        sticks[number].get();
        System.out.println("Philosopher nr " + number + " at position " + position +  " took left");
        sticks[(number +1)%sticks.length].get();
        System.out.println("Philosopher nr " + number + " at position " + position +  " took right");
        System.out.println("Philosopher nr " + number +" at position " + position +  " eating");
        sticks[number].letGo();
        System.out.println("Philosopher nr " + number + " at position " + position +  " let go of left");
        sticks[(number +1)%sticks.length].letGo();
        System.out.println("Philosopher nr " + number + " at position " + position +   " let go of right");
        kitchen.leave();
        System.out.println("Philosopher nr " + number + "has left kitchen");
    }
}
