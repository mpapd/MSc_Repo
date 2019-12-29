import { authHeader, handleResponse } from '../_helpers';

export const googleapi = {
    getApiKey,
    getCoordinates
};

function getApiKey() {

    return process.env.REACT_APP_API_KEY;
}

function getCoordinates(street,district,town){
    const requestOptions = { method: 'GET' };
    return fetch(`https://maps.googleapis.com/maps/api/geocode/json?address=`+street+district+town+`&key=`+process.env.REACT_APP_API_KEY, requestOptions).then(handleResponse);
}