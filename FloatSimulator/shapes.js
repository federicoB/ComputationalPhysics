//this class contain all the children of the superclass createjs.Shape

class DynamicObject extends createjs.Shape {
    constructor(density, graphic) {
        super(graphic);
        this.density = density;
        this.listOfForces = new Array();
        this.accelleration = new Vector(0, 0);
        this.speed = new Vector(0, 0);
    }

    setForce(name, vector) {
        this.listOfForces[name] = vector;
    }

    removeForce(name) {
        if (this.listOfForces[name] != undefined) {
            var newArray = new Array();
            for (var key in this.listOfForces) {
                if (key!=name) {
                    newArray[key] = this.listOfForces[key];
                }
            }
            this.listOfForces = newArray;
        }
    }

    getComputeForces() {
        var returnVectorX = 0, returnVectorY = 0;
        for (var key in this.listOfForces) {
            returnVectorX += Math.round(this.listOfForces[key].getXComponent());
            returnVectorY += Math.round(this.listOfForces[key].getYComponent());
        }
        ;
        return Vector.createFromComponents(returnVectorX, returnVectorY);
    }

    move(time) {
        var force = this.getComputeForces();
        this.accelleration.direction = force.direction;
        this.accelleration.module = force.module / 3;
        this.speed = Vector.createFromComponents(this.speed.getXComponent() + this.accelleration.getXComponent() * time,
            this.speed.getYComponent() + this.accelleration.getYComponent() * time);
        //the *-1 is because in computer graphics the y axe is reversed
        this.y += (this.speed.getYComponent() * -1) * time + 1 / 2 * (this.accelleration.getYComponent() * -1) * Math.pow(time, 2);
    }

    getCollisionPolygon() {
        var graphic = this.graphics;
        return (new SAT.Box(new SAT.Vector(this.x, this.y), graphic.width, graphic.height)).toPolygon();
    }
}

class Box extends DynamicObject {
    constructor(density, x, y, width, heigth) {
        if (density != undefined && x != undefined && y != undefined && width != undefined && heigth != undefined) {
            //TODO not create a new graphic for exery box
            var boxGraphic = new BoxGraphic(width, heigth);
            super(density, boxGraphic);
            this.x = x;
            this.y = y;
        } else {
            var boxGraphic = new BoxGraphic(view.width / 30, view.width / 30);
            //TODO change density
            super(0.1, boxGraphic);
            this.x = view.width / 2;
            this.y = view.height / 3;
        }
        this.graphics = boxGraphic;
        this.setForce("gravity", this.getWeight());
    }

    getWeight() {
        var area = this.graphics.width * this.graphics.height;
        var mass = area * this.density;
        var weigth = mass * 3;
        return new Vector((Math.PI * 3) / 2, weigth);
    }
}


class Pool extends DynamicObject {
    constructor() {
        var poolGraphic = new PoolGraphic(view.height / 3 + view.height / 20);
        //TODO change density
        super(1, poolGraphic);
        this.x = view.width / 3;
        this.baseHeight = poolGraphic.height;
        this.y = view.height / 2 + view.height / 20;
        this.baseY = this.y;
        this.graphics = poolGraphic;
    }

    calculateBuoyancyForce(area) {
        var mass = area * this.density;
        var weight = mass * 3;
        return new Vector(Math.PI / 2, weight);
    }

    increaseHeight(height) {
        this.graphics.setHeight(this.baseHeight + height);
        this.y = this.baseY - height;
    }
}