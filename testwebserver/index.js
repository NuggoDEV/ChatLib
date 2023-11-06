const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();

app.use(express.static('../assets'));

const endpoints = fs.readdirSync(path.join(__dirname, 'endpoints')).filter(file => file.endsWith('.js'));
endpoints.forEach(endpoint => {
    const route = '/api/' + endpoint.replace('.js', '');
    const handler = require('./endpoints/' + endpoint).default;
    app.get(route, handler);
});


app.listen(3000, () => {
    console.log('Server started at port 3000');
});