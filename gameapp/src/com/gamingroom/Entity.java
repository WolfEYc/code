package com.gamingroom;

public class Entity {
    private long id;
    private String name;

    private Entity(){}

    public Entity(long id, String name){
        this.id = id;
        this.name = name;
    }

    public long getId(){
        return this.id;
    }

    public String getName(){
        return this.name;
    }

    public String toString(){
        return this.id + " " + this.name;
    }
}
