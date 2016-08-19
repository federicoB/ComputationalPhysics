class Vector {
    constructor(direction,module) {
        this.direction = direction;
        this.module = module;
    }

}

class DynamicObject extends createjs.Shape {
    constructor(density,graphics) {
        super();
        this.density = density;
    }
}