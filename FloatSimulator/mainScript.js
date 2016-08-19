function init() {
    view = new View("canvas");
    createjs.Ticker.addEventListener("tick",Controller.tick);
    createjs.Ticker.framerate=30;
    var groundGraphic = new GroundGraphic();
    var groundShape = new createjs.Shape(groundGraphic);
    view.addChild(groundShape);
    var waterGraphic = new PoolGraphic();
    var waterShape = new createjs.Shape(waterGraphic);
    view.addChild(waterShape);
    var box = new Box();
    view.addChild(box);
}

class Controller {
    static tick() {
        view.updateDimensions();
        view.stage.update();
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
        this.canvas.setAttribute("width",this.width+"px");
        this.canvas.setAttribute("height",this.height+"px");
    }
}

class Vector {
    constructor(direction,module) {
        this.direction = direction;
        this.module = module;
    }

    static createFromComponents(x,y) {
        var module = Math.sqrt(Math.pow(x,2) + Math.pow(y,2));
        var direction = Math.atan2(y,x);
        return new Vector(direction,module);
    }

    getXcomponent() {
        return Math.cos(this.direction)*this.module;
    }

    getYComponent() {
        return Math.sen(this.direction)*this.module;
    }

}