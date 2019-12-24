import { authHeader, handleResponse } from '../_helpers';

export const userService = {
    getAll
};

function getAll() {
    const requestOptions = { method: 'GET', headers: authHeader() };
    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/applications`, requestOptions).then(handleResponse);
}