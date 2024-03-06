let cuisines = [];

function fetchCuisines() {
    return fetch(`http://localhost:8080/rest/api/cuisine`)
        .then(response => {
            if(!response.ok) {
                throw new Error('Failed to fetch cuisines!');
            }
            return response.json();
        })
        .then(data => {
            return data;
        })
        .catch(error => {
            console.error('Error fetching cuisines:', error);
            return [];
        });
}

function populateCuisineDropdown() {
    const cuisineDropdown = document.getElementById("newCooks");

    cuisines.forEach(cuisine => {
        const option = document.createElement("option");
        option.value = cuisine.cuisineId;
        option.text = cuisine.country;
        cuisineDropdown.add(option);
    });
}

async function preFillFieldsWithCurrentValues() {
    //const currentRestaurant = fetchRestaurantById(restaurantId);
    const restaurantId = getRestaurantIdFromURL();

    try {
        const restaurantDTO = await fetchRestaurantById(restaurantId);

        if(restaurantDTO) {
            document.getElementById("newName").value = restaurantDTO.name;
            document.getElementById("newPhone").value = restaurantDTO.phoneNumber;
            document.getElementById("newIOM").value = restaurantDTO.itemsOnMenu;
            document.getElementById("newOpenFrom").valueAsDate = new Date(restaurantDTO.openFrom);
            document.getElementById("newCooks").value = restaurantDTO.cooks;
        } else {
            console.error('Restaurant data not found.');
        }
    } catch (error) {
        console.error('Error pre-filling fields:', error);
    }
}

function updateRestaurant() {
    const updatedRestaurant = {
        name: document.getElementById("newName").value,
        phoneNumber: document.getElementById("newPhone").value,
        itemsOnMenu: document.getElementById("newIOM").value,
        openFrom: document.getElementById("newOpenFrom").value,
        cooksId: document.getElementById("newCooks").value
    };

    updateRestaurantFunction(updatedRestaurant);
}

async function updateRestaurantFunction(updatedRestaurant) {
    const restaurantId = getRestaurantIdFromURL();

    try {
        const response = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurantId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(updatedRestaurant),
        });
        if(!response.ok) {
            throw new Error(`Failed to update restaurant. Status: ${response.status}`);
        }
        const updatedRestaurantDTO = await response.json();
        console.log('Restaurant updated successfully!', updatedRestaurantDTO);
        window.location.href = 'index.html';
    } catch {
        console.error('Error updating restaurant:');
    }
}

function getRestaurantIdFromURL() {
    const urlParams = new URLSearchParams(window.location.search);
    return urlParams.get('restaurantId');
}

async function fetchRestaurantById(restaurantId) {
    try {
        const response = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurantId}`);

        if(!response.ok) {
            throw new Error(`Failed to fetch restaurant. Status: ${response.status}`);
        }
        const restaurantDTO = await response.json();
        return restaurantDTO;
    } catch (error) {
        console.error('Error fetching restaurant by ID:', error);
        return null;
    }
}

document.addEventListener("DOMContentLoaded", async function(){
    cuisines = await fetchCuisines();
    populateCuisineDropdown();

    const restaurantId = getRestaurantIdFromURL();
    preFillFieldsWithCurrentValues(restaurantId);
});