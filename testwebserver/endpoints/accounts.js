const express = require('express');

const sampledata = require('./sampledata.json');

async function endpoint(req, res) {
    const data = req.query;

    if (!data.action) {
        res.status(400).send('No action specified');
        return;
    }

    switch (data.action) {
        case 'list': {
            res.send(sampledata.accounts);
            break;
        }

        case 'delete': {
            if (!data.id) {
                res.status(400).send('No ID specified');
                return;
            }

            const accountjson = await sampledata.accounts.find(account => account.id === data.id);

            if (!accountjson) {
                res.status(404).send('Account not found');
                return;
            }

            console.log('Deleting account: ' + accountjson.name);

            res.status(200).send('Account deleted');
            break;
        }

        default: {
            res.status(400).send('Invalid action');
        }
    }
}

module.exports.default = endpoint;