function navbarCssInsert() {
    if(document.getElementById("navbarCss")) return;
    let node = document.createElement("link");
    node.setAttribute("rel", "stylesheet");
    node.setAttribute("href", "/navbar.css");
    node.setAttribute("id", "navbarCss");
    document.head.appendChild(node);
}

function navbarJsInsert() {
    if(document.getElementById("navbarJs")) return;
    let node = document.createElement("script");
    node.setAttribute("src", "/navbar.js");
    node.setAttribute("id", "navbarJs");
    document.body.appendChild(node);
}

function navbarHttpInsert(html) {
    if(document.getElementById("navbar")) return;
    let node = document.createElement("nav");
    node.setAttribute("id", "navbar");
    node.innerHTML = html;
    document.body.insertBefore(node, document.body.firstChild);
}