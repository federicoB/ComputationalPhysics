//this class contain all the children of the superclass createjs.Graphics

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
}

class PoolGraphic extends createjs.Graphics {
    constructor() {
        super();
        var width = view.width;
        var height = view.height;
        this.beginFill("#00ccff")
            .drawRect(width / 3, height / 2 + height / 20, width / 3, height / 2 - height / 10);
    }
}

class BoxGraphic extends createjs.Graphics {
    constructor(x,y,width,heigth) {
        super();
        this.beginFill("#993300").drawRect(x,y,width,heigth);
    }
}
