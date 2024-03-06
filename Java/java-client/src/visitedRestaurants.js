function goBack() {
    window.location.href = `index.html`;
}

async function showVisitedRestaurants(customerId) {
    try {
        const response = await fetch(`http://localhost:8080/rest/api/customer/${customerId}/visited`);
        const visitedRestaurants = await response.json();

        const visitedRestaurantsList = document.getElementById("visitedRestaurantsList");
        visitedRestaurantsList.innerHTML = "";

        await Promise.all(visitedRestaurants.map(async restaurant => {
            const cuisineResponse = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurant.restaurantId}/cooks`);
            const cuisineData = await cuisineResponse.json();
            const cuisineCountry = cuisineData.country;

            const restaurantDiv = document.createElement("div");
            restaurantDiv.innerHTML = `
                            <p>ID: ${restaurant.restaurantId}, ${restaurant.name}, Tel.: ${restaurant.phoneNumber}</p>
                            <p>${formatDate(restaurant.openFrom)}, items on menu: ${restaurant.itemsOnMenu}</p>
                            <p>Cuisine: ${cuisineCountry}</p>
                            <button onclick="removeVisited(${restaurant.restaurantId}, ${customerId})">Remove</button>
                            <hr>
                        `;
            visitedRestaurantsList.appendChild(restaurantDiv);
        }));
    } catch {
        console.error('Error!', error);
    }
}

function formatDate(date) {
    const options = {year: 'numeric', month: 'numeric', day: 'numeric'};
    return new Date(date).toLocaleDateString(undefined, options);
}

const urlParams = new URLSearchParams(window.location.search);
const customerId = urlParams.get('customerId');
if (customerId) {
    showVisitedRestaurants(customerId);
} else {
    console.error('Customers ID not provided in the url');
}

function addRestaurantToVisited() {
    window.location.href = `addVisited.html?customerId=${customerId}`;
}

async function removeVisited(restaurantId, customerId) {
    try {
        const confirmed = window.confirm(`Are you sure you want to remove this restaurant from the list of this customers (ID: ${customerId}) visited restaurants?`);

        if(!confirmed) {
            return;
        }

        const response = await fetch(`http://localhost:8080/rest/api/customer/${customerId}/visited/${restaurantId}`, {
            method: 'DELETE'
        });

        const contentType = response.headers.get('content-type');
        if(contentType && contentType.includes('application/json')) {
            await showVisitedRestaurants(customerId);
            window.location.href = `visitedRestaurants.html?customerId=${customerId}`;
        } else {
            console.error('Invalid content type in response.');
        }
    } catch (error) {
        console.error('Error removing visited restaurant.', error);
    }
}

