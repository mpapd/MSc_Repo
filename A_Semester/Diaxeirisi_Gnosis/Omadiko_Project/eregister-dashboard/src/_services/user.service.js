import { authHeader, handleResponse } from '../_helpers';

export const userService = {
    getAll,
    getSchools,
    getMusicSchools,
    getAthleticSchools
};

function getAll() {
    const requestOptions = { method: 'GET', headers: authHeader() };
    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/applications`, requestOptions).then(handleResponse);
}

function getSchools(town, district) {
    const requestOptions = { method: 'GET', headers: authHeader() };
    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/schools/` + town +`/`+district+`?category=1`, requestOptions).then(handleResponse);
}

function getMusicSchools(town) {
    const requestOptions = { method: 'GET', headers: authHeader() };
    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/schools/` + town +`?type=2`, requestOptions).then(handleResponse);
}

function getAthleticSchools(town) {
    const requestOptions = { method: 'GET', headers: authHeader() };
    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/schools/` + town +`?type=3`, requestOptions).then(handleResponse);
}