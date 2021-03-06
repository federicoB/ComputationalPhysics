
//declare a global variable view and globalConstants.
var view,globalConstants;

/**
 * First function of the program.
 */
function init() {
    //set the id of the canvas element of the page
    var canvasId = "canvas";
    //create a new view object
    view = View.getInstance(canvasId);
    //setup the ticker function
    createjs.Ticker.addEventListener("tick", Controller.tick);
    //set the framerate to 30. Now the ticker function is called 30 times a seconds.
    createjs.Ticker.framerate = 30;
    //create the globalConstants object
    globalConstants = new GlobalConstants();
    //create a new graphic for the ground
    var groundGraphic = GroundGraphicFactory.getDefaultInstance();
    //set the created graphic to a shape for the ground
    var groundShape = new createjs.Shape(groundGraphic);
    //add the shape of the ground to the view
    view.addChild(groundShape);
    //create a new pool
    var water = new Pool();
    //add it to the view
    view.addChild(water);
    //create a new box
    var box = new Box();
    //add it to the view
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

    /**
     * get the singleton instance of the view
     * @param canvasId: the id of the canvas element
     * @returns {View}: the view object.
     */
    static getInstance (canvasId) {
        //if the view is not yet defined
        if (typeof view === 'undefined') {
            //create a new view and return it
            return new View(canvasId);
        } else {
            //otherwise return the already created object.
            return view;
        }
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

class GlobalConstants {
    constructor() {
        this.gravitationalAcceleration = 9.8;
    }
}