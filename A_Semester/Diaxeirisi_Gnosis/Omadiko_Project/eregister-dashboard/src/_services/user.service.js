import { authHeader, handleResponse } from '../_helpers';

export const userService = {
    getAll,
    getSchools,
    getMusicSchools,
    getAthleticSchools,
    saveApplication
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


function saveApplication(firstname, lastname, fathername, mothername, birthdate, town, townEng, district, districtEng, street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments ) {
    const body = {firstname : firstname, lastname : lastname,fathername : fathername,mothername : mothername,
    birthdate : birthdate,town : town,townEng : townEng,district : district,districtEng : districtEng,street : street,
    foreignLanguage1 : foreignLanguage1, foreignLanguage2 : foreignLanguage2, optionalClass1 : optionalClass1, optionalClass2 : optionalClass2, school_id : school_id,comments : comments}

    const requestOptions = { method: 'POST',body: JSON.stringify(

        body
          
    ), headers: authHeader()};



    return fetch(`http://eregister-backend.herokuapp.com/orchestrator/application`, requestOptions
    
    ).then(handleResponse);
}