function init() {
    view = new View("canvas");
    createjs.Ticker.addEventListener("tick",Controller.tick);
    createjs.Ticker.framerate=30;
    var groundGraphic = new Ground();
    var groundShape = new createjs.Shape(groundGraphic);
    view.stage.addChild(groundShape);
    var waterGraphic = new Pool();
    var waterShape = new createjs.Shape(waterGraphic);
    view.stage.addChild(waterShape);
    var boxGraphic = new Box();
    var boxShape = new createjs.Shape(boxGraphic);
    view.stage.addChild(boxShape);
}

class Controller {
    static tick() {
        view.updateDimensions();
        view.stage.update();
    }
}