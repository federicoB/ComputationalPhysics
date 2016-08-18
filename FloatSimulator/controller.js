function init() {
    view = new View("canvas");
    createjs.Ticker.addEventListener("tick",Controller.tick);
    createjs.Ticker.framerate=30;
    var groundGraphic = new createjs.Graphics()
        //.beginFill("green").drawRect(0,view.height/2,view.width,view.height/2);
        //start of the ground
        .moveTo(0,view.height/2).beginFill("green")
        //start of the pool
        .lineTo(view.width/3,view.height/2)
        //left base of the pool
        .lineTo(view.width/3,view.height-view.height/10)
        //right base of the pool
        .lineTo(2*(view.width/3),view.height-view.height/10)
        //top right of the pool
        .lineTo(2*(view.width/3),view.height/2)
        //top end of the groud
        .lineTo(view.width,view.height/2)
        //bottom end of the ground
        .lineTo(view.width,view.height)
        //bottom left of the ground
        .lineTo(0,view.height)
        //close the poly
        .lineTo(0,view.height/2)
    var groundShape = new createjs.Shape(groundGraphic);
    view.stage.addChild(groundShape);
    var waterGraphic = new createjs.Graphics().beginFill("#00ccff")
        .drawRect(view.width/3,view.height/2+view.height/20,view.width/3,view.height/2-view.height/10);
    var waterShape = new createjs.Shape(waterGraphic);
    view.stage.addChild(waterShape);
}

class Controller {
    static tick() {
        view.updateDimensions();
        view.stage.update();
    }
}