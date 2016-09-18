//The graphic is a virtual object, it's the design of the shape.

class GroundGraphic extends createjs.Graphics {
    constructor() {
        super();
        var width = view.width;
        var height = view.height;
        //start of the ground
        this.moveTo(0, height / 2).beginFill("green")
        //start of the pool
            .lineTo(width / 3, height / 2)
            //left base of the pool
            .lineTo(width / 3, height - height / 10)
            //right base of the pool
            .lineTo(2 * (width / 3), height - height / 10)
            //top right of the pool
            .lineTo(2 * (width / 3), height / 2)
            //top end of the groud
            .lineTo(width, height / 2)
            //bottom end of the ground
            .lineTo(width, height)
            //bottom left of the ground
            .lineTo(0, height)
            //close the poly
            .lineTo(0, height / 2);
    }
    addHole(hole) {

    }
}

//TODO check if this is the correct file for this class
class GroundGraphicFactory {
    static getDefaultInstance() {

    }
}

class HoleFactory {
    static getDefaultInstance() {
        var width= view.width/3;
        var height = (view.height*2)/5;
    }
    static getInstance(width,depth) {
        return new Hole(width,depth);
    }
}

class Hole {
    constructor(width,depth) {
        this.width = width;
        this.depth = depth;
    }
}

class PoolGraphic extends createjs.Graphics {
    constructor(height) {
        super();
        this.width = view.width/3;
        this.height = height;
        this.drawcommand = this.beginFill("#00ccff")
            .drawRect(0,0,this.width,this.height).command;
    }
    setHeight(height) {
        this.drawcommand.h = height;
        this.height = height;
    }
}

class BoxGraphic extends createjs.Graphics {
    constructor(width,height) {
        super();
        this.width = width;
        this.height = height;
        this.beginFill("#993300").drawRect(0,0,width,height);
    }
}
