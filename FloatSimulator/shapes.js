//this class contain all the children of the superclass createjs.Shape

class DynamicObject extends createjs.Shape {
    constructor(density, graphic) {
        super(graphic);
        this.density = density;
        this.listOfForces = new Array();
        this.accelleration = new Vector(0,0);
        this.speed = new Vector(0,0)
    }
    addForce(name,vector) {
        this.listOfForces[name] = vector;
    }
    getComputeForces() {
        var returnVectorX = 0,returnVectorY = 0;
        for (var key in this.listOfForces) {
            returnVectorX += this.listOfForces[key].getXComponent();
            returnVectorY += this.listOfForces[key].getYComponent();
        };
        return Vector.createFromComponents(returnVectorX,returnVectorY);
    }
    move(time) {
        //TODO fix for multiple direction
        var force = this.getComputeForces();
        this.accelleration.direction = force.direction;
        this.accelleration.module = force.module/2;
        this.speed.direction = this.accelleration.direction;
        this.speed.module += this.accelleration.module * time;
        this.y += this.speed.module*time + 1/2*this.accelleration.module*Math.pow(time,2);
    }
}

class Box extends DynamicObject {
    constructor(density, x, y, width, heigth) {
        if (density != undefined && x != undefined && y != undefined && width != undefined && heigth != undefined) {
            //TODO not create a new graphic for exery box
            super(density, new BoxGraphic(x, y, width, heigth));
        } else {
            //TODO change density
            super(1, new BoxGraphic(0, 0, view.width / 50, view.width / 50));
            this.x = view.width / 2;
            this.y = view.height / 3;
            this.width = view.width / 50;
            this.heigth = view.width / 50;
        }
        this.addForce("gravity",this.getWeight());
    }
    getWeight() {
        var area = this.width * this.heigth;
        var mass = area*this.density;
        var weigth = mass * 2;
        return new Vector(270,weigth);
    }
    getCollisionBox() {

    }
}

class Pool extends createjs.Shape {
    constructor() {
        var poolGraphic = new PoolGraphic();
        super(poolGraphic);
        this.x = view.width/3;
        this.y= view.height/2 + view.height/20;
        this.graphics = poolGraphic;
    }

    getCollisionBox() {
        var graphic = this.graphics;
        return new SAT.Box(new SAT.Vector(graphic.x,graphic.y),graphic.width,graphic.height);
    }
}