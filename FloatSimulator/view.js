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