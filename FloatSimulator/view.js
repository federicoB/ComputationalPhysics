class View {
    constructor(canvasID) {
        this.canvas = document.getElementById(canvasID);
        this.stage = new createjs.Stage(canvasID);
        this.updateDimensions();
    }
    updateDimensions() {
        this.width = document.body.clientWidth;
        this.height = document.body.clientHeight;
        this.canvas.setAttribute("width",this.width+"px");
        this.canvas.setAttribute("height",this.height+"px");
    }
}

class Ground extends createjs.Graphics {
    constructor() {
        super();
        //start of the ground
        this.moveTo(0, view.height / 2).beginFill("green")
        //start of the pool
            .lineTo(view.width / 3, view.height / 2)
            //left base of the pool
            .lineTo(view.width / 3, view.height - view.height / 10)
            //right base of the pool
            .lineTo(2 * (view.width / 3), view.height - view.height / 10)
            //top right of the pool
            .lineTo(2 * (view.width / 3), view.height / 2)
            //top end of the groud
            .lineTo(view.width, view.height / 2)
            //bottom end of the ground
            .lineTo(view.width, view.height)
            //bottom left of the ground
            .lineTo(0, view.height)
            //close the poly
            .lineTo(0, view.height / 2);
    }
}

class Pool extends createjs.Graphics {
    constructor() {
        super();
        this.beginFill("#00ccff")
            .drawRect(view.width / 3, view.height / 2 + view.height / 20, view.width / 3, view.height / 2 - view.height / 10);
    }
}