const express = require('express');
const fs = require('fs');
const path = require('path');

const server = express();

server.use(express.static("../assets/"));

server.listen(3000, () => {
    console.log("Webserver is running");
});