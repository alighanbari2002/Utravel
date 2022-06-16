//send post request for logout
function logout() {
    document.getElementById("logoutForm").submit();
}

//hide navbar on scroll
let prevScrollpos = window.pageYOffset;
window.onscroll = function () {
    document.getElementById("navbar").style.top = (prevScrollpos > window.pageYOffset) ? "0" : "-60px";
    prevScrollpos = window.pageYOffset;
}