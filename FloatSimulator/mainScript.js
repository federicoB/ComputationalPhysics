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
    var boxGraphic = new BoxGraphic();
    var boxShape = new createjs.Shape(boxGraphic);
    view.addChild(boxShape);
    var gravitationalForce = new Vector(270,9,8);
}

class Controller {
    static tick() {
        view.updateDimensions();
        view.stage.update();
    }
}