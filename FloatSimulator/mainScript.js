/**
 * First function of the program.
 */
function init() {
    var canvasId = "canvas";
    view = new View(canvasId);
    createjs.Ticker.addEventListener("tick", Controller.tick);
    createjs.Ticker.framerate = 30;
    world = new World();
    var groundGraphic = new GroundGraphic();
    var groundShape = new createjs.Shape(groundGraphic);
    view.addChild(groundShape);
    var water = new Pool();
    view.addChild(water);
    var box = new Box();
    view.addChildAt(box, 2);
}

class Controller {
    static tick(event) {
        view.updateDimensions();
        var box = view.getChildAt(2);
        var pool = view.getChildAt(1);
        var response = new SAT.Response();
        var collided = SAT.testPolygonPolygon(box.getCollisionPolygon(),pool.getCollisionPolygon(),response);
        var overlap = 0, area = 0;
        if (collided) {
            overlap = response.overlap;
            if (overlap>box.graphics.height) overlap = box.graphics.height;
            area = overlap * box.graphics.width;
            box.setForce("buoyancy",pool.calculateBuoyancyForce(area));
        } else {
            box.removeForce("buoyancy");
        }
        pool.increaseHeight(area/pool.graphics.width);
        box.move(event.delta / 1000);
        view.update();
    }
}

class View extends createjs.Stage {
    constructor(canvasID) {
        super(canvasID);
        this.canvas = document.getElementById(canvasID);
        this.updateDimensions();
    }

    updateDimensions() {
        this.width = document.body.clientWidth;
        this.height = document.body.clientHeight;
        this.canvas.setAttribute("width", this.width + "px");
        this.canvas.setAttribute("height", this.height + "px");
    }
}

class Vector {
    constructor(direction, module) {
        this.direction = direction;
        this.module = module;
    }

    static createFromComponents(x, y) {
        var module = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
        var direction = Math.atan2(y, x);
        return new Vector(direction, module);
    }

    getXComponent() {
        return Math.cos(this.direction) * this.module;
    }

    getYComponent() {
        return Math.sin(this.direction) * this.module;
    }

}

class World {
    constructor() {
        this.gravitationalAcceleration = 9.8;
    }
}