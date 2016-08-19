//this class contain all the children of the superclass createjs.Shape

class DynamicObject extends createjs.Shape {
    constructor(density, graphic) {
        super(graphic);
        this.density = density;
        this.listOfForces = new Array();
    }
    addForce(name,vector) {
        listOfForces[name] = vector;
    }
    getComputeForces() {

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

    }
    getWeight() {
        var area = width * height;
        var mass = width*this.density;
        var weigth = mass * 9.8;
        return new Vector(270,weigth);
    }
}