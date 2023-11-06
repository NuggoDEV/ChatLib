# ChatLib API Doc - ``/api/accounts``

## Overview

The ``/api/accounts`` endpoint is used to manage accounts. The action is specified in the request json with datafield ``action``. Currently, the following actions are supported:

| Action | Description | Request JSON | Response JSON                                              |
|--------|-------------|--------------|------------------------------------------------------------|
| ``list`` | List all accounts | ``{"action": "list"}`` | ``[{"id":"id","name":"accountname","type":"accounttype"}`` |
| ``delete`` | Delete an account | ``{"action": "delete", "id": "accountid"}`` | ``HTTP 200 - Success`` / ``Http Error`` + Status Message   |
