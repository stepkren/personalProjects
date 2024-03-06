document.addEventListener("DOMContentLoaded", function () {
    const showCustomersBtn = document.getElementById("showCustomersBtn");
    const showRestaurantsBtn = document.getElementById("showRestaurantsBtn");
    const showCuisinesBtn = document.getElementById("showCuisinesBtn");
    const customerList = document.getElementById("customerList");
    const restaurantList = document.getElementById("restaurantList");
    const cuisineList = document.getElementById("cuisineList");

    showCustomersBtn.addEventListener("click", function () {
        console.log("Show Customers Button Clicked!");
        clearListsExcept(customerList);
       fetch('http://localhost:8080/rest/api/customer')
           .then(response => response.json())
           .then(data => {
               customerList.innerHTML = "<h2>Customer List</h2>";
               data.forEach(customer => {
                   const customerDiv = document.createElement("div");
                   customerDiv.innerHTML = `
                        <p>ID: ${customer.customerId}, ${customer.name}, Email: ${customer.email}, Tel.: ${customer.phoneNumber}</p>
                        <button onclick="updateCustomer(${customer.customerId}, '${customer.name}', '${customer.phoneNumber}', '${customer.email}')">Update Customer</button>
                        <button onclick="deleteCustomer(${customer.customerId})">Delete Customer</button>
                        <button onclick="getVisited(${customer.customerId})">Visited Restaurants</button>
                        <hr>
                   `;
                   customerList.appendChild(customerDiv);
               });
               insertAddCustomerButton();
           })
           .catch(error => {
              console.error('Error', error);
           });
    });

    showRestaurantsBtn.addEventListener("click", async function () {
        console.log("Show Restaurants Button Clicked");
        clearListsExcept(restaurantList);

        try {
            const response = await fetch(`http://localhost:8080/rest/api/restaurant`);
            const data = await response.json();

            restaurantList.innerHTML = '<h2>Restaurant List</h2>';
            await Promise.all(data.map(async restaurant => {
                const cuisineResponse = await fetch(`http://localhost:8080/rest/api/restaurant/${restaurant.restaurantId}/cooks`);
                const cuisineData = await cuisineResponse.json();
                const cuisineCountry = cuisineData.country;

                const restaurantDiv = document.createElement("div");
                restaurantDiv.innerHTML = `
                        <p>ID: ${restaurant.restaurantId}, ${restaurant.name}, Tel.: ${restaurant.phoneNumber}</p>
                        <p>${formatDate(restaurant.openFrom)}, items on menu: ${restaurant.itemsOnMenu}</p>      
                        <p>Cuisine: ${cuisineCountry}</p>                
                        <button onclick="updateRestaurant(${restaurant.restaurantId})">Update Restaurant</button>
                        <button onclick="deleteRestaurant(${restaurant.restaurantId})">Delete Restaurant</button>
                        <hr>
                    `;
                restaurantList.appendChild(restaurantDiv);
            }));
            insertAddRestaurantButton();

        } catch (error) {
            console.error('Error!', error);
        }
    });

    function formatDate(date) {
        const options = {year: 'numeric', month: 'numeric', day: 'numeric'};
        return new Date(date).toLocaleDateString(undefined, options);
    }

    showCuisinesBtn.addEventListener("click", function() {
       console.log("Show Cuisines Button Clicked!");
       clearListsExcept(cuisineList);
       fetch(`http://localhost:8080/rest/api/cuisine`)
           .then(response => response.json())
           .then(data => {
               cuisineList.innerHTML = '<h2>Cuisine List</h2>';
               data.forEach(cuisine => {
                   const cuisineDiv = document.createElement("div");
                   cuisineDiv.innerHTML = `
                        <p>ID: ${cuisine.cuisineId}, ${cuisine.country}</p>
                        <button onclick="updateCuisine(${cuisine.cuisineId}, '${cuisine.country}')">Update Cuisine</button>
                        <button onclick="deleteCuisine(${cuisine.cuisineId})">Delete Cuisine</button>
                        <button onclick="findCustomersVisitedRestaurantCookingCuisine(${cuisine.cuisineId})">Find Customers That Visited A Restaurant Cooking This Cuisine</button>
                        <hr>
                   `;
                   cuisineList.appendChild(cuisineDiv);
               });
               insertAddCuisineButton();
           })
           .catch(error => {
               console.error('Error', error);
           });
    });

    function clearListsExcept (exceptList) {
        const allLists = [cuisineList, customerList, restaurantList];
        allLists.forEach(list => {
           if (list !== exceptList) {
               list.innerHTML = '';
           }
        });
    }

    window.updateCustomer = function(customerId, customerName, customerPhone, customerEmail) {
        console.log(`Update customer with ID: ${customerId}`);

        const updatedName = prompt("Enter new (if you wish to keep the old name, type it again) name:", customerName);
        const updatedPhone = prompt("Enter new (if you wish to keep the old phone number, type it again) phone number:", customerPhone);
        const updatedEmail = prompt("Enter new (if you wish to keep the old email, type it again) email:", customerEmail);

        console.log('New name: ', updatedName);
        console.log('New phone number: ', updatedPhone);
        console.log('New email: ', updatedEmail);

        const updatedCustomer = {
            customerId: customerId,
            name: updatedName,
            phoneNumber: updatedPhone,
            email: updatedEmail
        };

        fetch(`http://localhost:8080/rest/api/customer/${customerId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(updatedCustomer)
        })
            .then(response => response.json())
            .then(updatedCustomer => {
                console.log('Customer updated:', updatedCustomer);
                showCustomers();
            })
            .catch(error => {
                console.error('Error updating customer:', error);
            });
    };

    window.updateRestaurant = function (restaurantId) {
        console.log(`Update restaurant with ID: ${restaurantId}`);
        window.location.href = `updateRestaurant.html?restaurantId=${restaurantId}`;
    }

    window.updateCuisine = function (cuisineId, country) {
        console.log(`Update cuisine with ID: ${cuisineId}`);

        const updatedCountry = prompt("Enter new (if you wish to keep the old country, type it again) country:", country);

        console.log("New country: ", updatedCountry);

        const updatedCuisine = {
            cuisineId: cuisineId,
            country: updatedCountry
        };

        fetch(`http://localhost:8080/rest/api/cuisine/${cuisineId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(updatedCuisine)
        })
            .then(response => response.json())
            .then(updatedCuisine => {
                console.log('Cuisine updated:', updatedCuisine);
                showCuisines();
            })
            .catch(error => {
                console.error('Error updating cuisine:', error);
            });
    }

    window.deleteCustomer = function(customerId) {
        console.log(`Delete customer with ID: ${customerId}`);

        if(confirm("Are you sure you want to delete this customer?")) {
            fetch(`http://localhost:8080/rest/api/customer/${customerId}`, {
                method: 'DELETE',
            })
                .then(response => {
                    if(!response.ok) {
                        throw new Error(`HTTP error! Status: ${response.status}`);
                    }

                    const contentType = response.headers.get('content-type');
                    if(contentType && contentType.includes('application/json')) {
                        return response.json();
                    } else {
                        return {};
                    }
                })
                .then(deleteCustomer => {
                    console.log('Customer deleted successfully.');
                    showCustomers();
                })
                .catch(error => {
                    console.error('Error deleting customer', error);
                });
        }

    }

    window.deleteRestaurant = function (restaurantId) {
        console.log(`Delete restaurant with ID: ${restaurantId}`);

        if(confirm("Are you sure you want to delete this restaurant?")) {
            fetch(`http://localhost:8080/rest/api/restaurant/${restaurantId}`, {
                method: 'DELETE',
            })
                .then(response => {
                    if(!response.ok) {
                        throw new Error(`HTTP error! Status: ${response.status}`);
                    }

                    const contentType = response.headers.get('content-type');
                    if(contentType && contentType.includes('application/json')) {
                        return response.json();
                    } else {
                        return {};
                    }
                })
                .then(deleteRestaurant => {
                    console.log('Restaurant deleted successfully.');
                    showRestaurants();
                })
                .catch(error => {
                   console.error('Error deleting restaurant', error);
                });
        }
    }

    window.deleteCuisine = function (cuisineId) {
        console.log(`Delete cuisine with ID: ${cuisineId}`);

        if(confirm("Are you sure you want to delete this cuisine? DELETING THIS CUISINE WILL ALSO DELETE ALL RESTAURANTS THAT COOK THIS CUISINE!!")) {
            fetch(`http://localhost:8080/rest/api/cuisine/${cuisineId}`, {
                method: 'DELETE',
            })
                .then(response => {
                    if(!response.ok) {
                        throw new Error(`HTTP error! Status: ${response.status}`);
                    }

                    const contentType = response.headers.get('content-type');
                    if(contentType && contentType.includes('application/json')) {
                        return response.json();
                    } else {
                        return {};
                    }
                })
                .then(deleteRestaurant => {
                    console.log('Cuisine deleted successfully.');
                    showCuisines();
                })
                .catch(error => {
                    console.error('Error deleting cuisine', error);
                });
        }
    }

    window.getVisited = function(customerId) {
        redirectToVisitedRestaurants(customerId);
    }

    function insertAddCustomerButton() {
        const addButton = document.createElement("button");
        addButton.textContent = "Add Customer";
        addButton.onclick = function () {
            console.log("Add Customer button clicked!");
            addCustomer();
        };
        const customerList = document.getElementById("customerList");
        customerList.appendChild(addButton);
    }

    function insertAddRestaurantButton() {
        const addButton = document.createElement("button");
        addButton.textContent = "Add Restaurant";
        addButton.onclick = function () {
            console.log("Add Restaurant button clicked!");
            addRestaurant();
        };
        const restaurantList = document.getElementById("restaurantList");
        restaurantList.appendChild(addButton);
    }

    function insertAddCuisineButton() {
        const addButton = document.createElement("button");
        addButton.textContent = "Add Cuisine";
        addButton.onclick = function () {
            console.log("Add Cuisine button clicked!");
            addCuisine();
        };
        const cuisineList = document.getElementById("cuisineList");
        cuisineList.appendChild(addButton);
    }

    function addCustomer() {
        const customerName = prompt("Enter customer name:");
        const customerPhone = prompt("Enter customer phone number:");
        const customerEmail = prompt("Enter customer email:");

        const newCustomer = {
            name: customerName,
            phoneNumber: customerPhone,
            email: customerEmail
        };

        fetch(`http://localhost:8080/rest/api/customer`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(newCustomer)
        })
            .then(response => response.json())
            .then(createdCustomer => {
                console.log('Customer created successfully:', createdCustomer);
                showCustomers();
            })
            .catch(error => {
                console.error('Error creating customer:', error);
                alert("Error creating customer! Please check your input data and try again.");
            });
    }

    function addRestaurant() {
        window.location.href = 'addRestaurant.html';
    }

    function addCuisine() {
        const cuisineCountry = prompt("Enter country of cuisine:");

        const newCuisine = {
            country: cuisineCountry,
        };

        fetch(`http://localhost:8080/rest/api/cuisine`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(newCuisine)
        })
            .then(response => response.json())
            .then(createdCuisine => {
                console.log('Cuisine created successfully:', createdCuisine);
                showCuisines();
            })
            .catch(error => {
                console.error('Error creating cuisine:', error);
                alert("Error creating cuisine! Please check your input data and try again.");
            });
    }

    function showCustomers() {
        const showCustomersBtn = document.getElementById("showCustomersBtn");
        showCustomersBtn.click();
    }

    function showRestaurants() {
        const showRestaurantsBtn = document.getElementById("showRestaurantsBtn");
        showRestaurantsBtn.click();
    }

    function showCuisines() {
        const showCuisinesBtn = document.getElementById("showCuisinesBtn");
        showCuisinesBtn.click();
    }

    function redirectToVisitedRestaurants (customerId) {
        window.location.href = `visitedRestaurants.html?customerId=${customerId}`;
    }

    window.findCustomersVisitedRestaurantCookingCuisine = function (cuisineId) {
        window.location.href = `findCustomersVisiting.html?cuisineId=${encodeURIComponent(cuisineId)}`;
    }
});