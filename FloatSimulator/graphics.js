//The graphic is a virtual object, it's the design of the shape.

/**
 * The graphic representing the ground. A ground can have multiple holes in it.
 */
class GroundGraphic extends createjs.Graphics {
    //create an empty groundgraphic
    constructor() {
        //call the super constructor for creating createjs.Graphics base class
        super();
        //create an empty array for cointaing the holes
        this.holes = SortedList.create();
    }
    //call this when ready to draw the ground
    drawGraphic() {
        //get the width of the canvas and save it on a local variable
        var width = view.width;
        //get the height of the canvas and save it on a local variable
        var height = view.height;
        //define a local variable for containing the current abscissa of drawing point. Initialize it to 0.
        var x=0;
        //define a local variable for containing the current ordinate of drawing point. Initialize it to half the height of the canvas.
        var y=height/2;
        //move the drawing point to the initial position and start filling the graphic with green color
        this.moveTo(x, y).beginFill("green");
        //for every hole object in the holes array
        for (var holeObject of this.holes) {
            //set the abscissa to the leftmargin of the hole
            x=holeObject.leftMargin;
            this.lineTo(x,y);
            //move the point to the left bottom of the hole
            y+=holeObject.hole.depth;
            this.lineTo(x,y);
            //move the point to the right bottom of the hole
            x+=holeObject.hole.width;
            this.lineTo(x,y);
            //move the point to the right top of the hole
            y-=holeObject.hole.depth;
            this.lineTo(x,y);
        }
        //set tha absissa to the end of the ground
        x=width;
        this.lineTo(x,y);
        //draw a line to close the right part of the ground
        y=height;
        this.lineTo(x,y);
        //draw a line to close the bottom part of the ground
        x=0;
        this.lineTo(x,y);
        //draw a line to close the left part of the ground
        y=height/2;
        this.lineTo(x,y);
        //close the drawn path and complete the filling
        this.closePath().endFill();
        //return this for method chaining
        return this;
    }

    /**
     * Add a hole to the ground graphic object
     * @param hole: the object representing the hole. It must have properties for width and depth
     * @param leftMargin: the leftmargin of the hole from the left start of the ground
     * @returns {GroundGraphic} return the ground graphic for method chaining
     */
    addHole(hole,leftMargin) {
        //check if the hole does't overlap with an existing hole
        var overlap = false;
        for (holeObject of this.holes) {
            if (leftMargin < holeObject.leftMargin) {
                if (leftMargin+hole.width>holeObject.leftMargin) {
                    overlap = true;
                }
            } else {
                if (holeObject.leftMargin+holeObject.hole.width>leftMargin) {
                    overlap = true;
                }
            }
        }
        if (!overlap) {
            this.holes.insertOne({hole: hole, leftMargin: leftMargin});
        }
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
        this.beginFill("#993300").drawRect(0,0,width,height).endFill();
    }
}
