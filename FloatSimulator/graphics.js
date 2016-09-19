//The graphic is a virtual object, it's the design of the shape.

class GroundGraphic extends createjs.Graphics {
    constructor() {
        super();
        this.holes = [];
    }
    drawGraphic() {
        var width = view.width;
        var height = view.height;
        var x=0,y=height/2;
        //start of the ground
        this.moveTo(x, y).beginFill("green");
        for (var holeObject of this.holes) {
            x=holeObject.leftMargin;
            this.lineTo(x,y);
            y+=holeObject.hole.depth;
            this.lineTo(x,y);
            x+=holeObject.hole.width;
            this.lineTo(x,y);
            y-=holeObject.hole.depth;
            this.lineTo(x,y);
        }
        x=width;
        this.lineTo(x,y);
        y=height;
        this.lineTo(x,y);
        x=0;
        this.lineTo(x,y);
        y=height/2;
        this.lineTo(x,y);
        this.closePath().endFill();
        return this;
    }
    addHole(hole,leftMargin) {
        this.holes.push({hole : hole,leftMargin : leftMargin});
        //TODO sort holes array or insert in right position
        return this;
    }
}

//TODO check if this is the correct file for this class
class GroundGraphicFactory {
    static getDefaultInstance() {
        return new GroundGraphic().addHole(HoleFactory.getDefaultInstance(),view.width/3).drawGraphic();
    }
}

class HoleFactory {
    static getDefaultInstance() {
        var width= view.width/3;
        var depth = (view.height*2)/5;
        return new Hole(width,depth);
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
