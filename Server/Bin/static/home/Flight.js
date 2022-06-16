class Flight {
    constructor(id, airline, departure, destinarion, cost) {
        this.id_ = id;
        this.airline = airline;
        this.departure = departure;
        this.destinarion = destinarion;
        this.cost = cost;
        this.imglink = "./hich.jpeg";
    };

    get id() { return this.id_; };
    get airline() { return this.airline; };
    get departure() { return this.departure; };
    get destinarion() { return this.destinarion; };
    get cost() { return this.cost; };

    toHtml(btnText) {
        return `<div class="imgContainer"><img src="` + this.imglink + `" alt="recipe ` + this.id + `'s image" title="` + this.title + `"></img></div>
        <p>ID: ` + this.id + `</p>
        <p>Airline: ` + this.airline + `</p>
        <p>Departure: ` + this.departure + `</p>
        <p>Destinarion: ` + this.destinarion + `</p>
        <p>Cost: ` + this.cost + `</p>
        <span class="btnFuture" onclick="recipeBtnFunc(this)" id="` + this.id + `">` + btnText + `</span>`;
    };
};

function addFlight(flight, id, btnText) {
    if (!(flight instanceof Flight)) {
        throw "Non flight passed to addFlight."
    }
    let node = document.createElement("div");
    node.setAttribute("class", "flight");
    node.setAttribute("id", id);
    node.innerHTML = flight.toHtml(btnText);
    document.getElementById("flights").appendChild(node);
}