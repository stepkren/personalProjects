async function fetchRestaurants() {
    try {
        const response = await fetch(`http://localhost:8080/rest/api/restaurant`);
        const data = await response.json();

        if(data.length === 0) {
            alert('Error! There are no restaurants to chose from.');
            goBack();
        }

        return data;

    } catch (error) {
        console.error('Error fetching restaurants!', error);
        throw error;
    }
}

function goBack() {
    window.location.href = `visitedRestaurants.html?customerId=${customerId}`;
}

async function loadRestaurants() {
    try {
        const restaurants = await fetchRestaurants();

        const restaurantList = document.getElementById("restaurantList");
         await Promise.all(restaurants.map(async restaurant => {

           const cuisineResponse = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurant.restaurantId}/cooks`);
           const cuisineData = await cuisineResponse.json();
           const cuisineCountry = cuisineData.country;

           const restaurantDiv = document.createElement('div');
           restaurantDiv.innerHTML = `
                <p>ID: ${restaurant.restaurantId}, ${restaurant.name}, Tel.: ${restaurant.phoneNumber}</p>
                <p>${formatDate(restaurant.openFrom)}, items on menu: ${restaurant.itemsOnMenu}</p>
                <p>Cuisine: ${cuisineCountry}</p>
                <button onclick="addVisited(${restaurant.restaurantId}, ${customerId})">Add</button>
                <hr>
           `;
           restaurantList.appendChild(restaurantDiv);
        }));
    } catch (error) {
        alert('Error loading restaurants. Please try again later.')
    }
}

function formatDate(date) {
    const options = {year: 'numeric', month: 'numeric', day: 'numeric'};
    return new Date(date).toLocaleDateString(undefined, options);
}

const urlParams = new URLSearchParams(window.location.search);
const customerId = urlParams.get('customerId');
if (customerId) {
    console.log(`ID: ${customerId}`);
} else {
    console.error('Customers ID not provided in the url');
}

async function addVisited(restaurantId, customerId) {
    console.log(`customerId: ${customerId} | restaurantId: ${restaurantId}`);

    try {

        const confirmation = window.confirm(`Are you sure you want to add this restaurant to the list of this customers (ID: ${customerId}) visited restaurants?`);

        if(!confirmation) {
            return;
        }

        const restaurantResponse = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurantId}`);
        const restaurantData = await restaurantResponse.json();

        const currentDate = new Date();
        const openFromDate = new Date(restaurantData.openFrom);

        if(currentDate >= openFromDate) {
            const addVisitedResponse = await fetch(`http://localhost:8080/rest/api/customer/${customerId}/visited`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(restaurantId)
            });
            if(addVisitedResponse.ok) {
                alert(`Restaurant added to the list of customer's (${customerId}) visited restaurants successfully.`);
            } else {
                alert(`Error adding visited restaurant.`);
            }
        } else {
            alert("Error adding visited restaurant. This restaurant isn't yet open.");
        }
    } catch (error) {
        console.error('Error:', error);
    }
}

window.onload = loadRestaurants;