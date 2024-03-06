document.addEventListener("DOMContentLoaded", function () {
    fetchCuisines();
})

async function fetchCuisines() {
    const cuisines = document.getElementById("newCooks");

    try{
        const response = await fetch(`http://localhost:8080/rest/api/cuisine`);
        const data = await response.json();

        if(data.length === 0) {
            alert("Cannot create restaurant. There are no cuisines available. Try again later.");
            goBack();
        }

        data.forEach(cuisine => {
           const option = document.createElement("option");
           option.value = cuisine.cuisineId;
           option.textContent = cuisine.country;
           cuisines.appendChild(option);
        });
    } catch {
        console.error('Error fetching cuisines!', error);
    }
}

async function addRestaurant() {
    const createdRestaurant = {
        name: document.getElementById("newName").value,
        phoneNumber: document.getElementById("newPhone").value,
        itemsOnMenu: document.getElementById("newIOM").value,
        openFrom: document.getElementById("newOpenFrom").value,
        cooksId: document.getElementById("newCooks").value
    };

    try{
        const response = await fetch(`http://localhost:8080/rest/api/restaurant`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(createdRestaurant),
        });
        if(!response.ok) {
            throw new Error(`Failed to create restaurant. Status: ${response.status}`);
        }
        console.log('Restaurant added successfully!');
        window.location.href = 'index.html';
    } catch (error) {
        console.error('Error adding restaurant:', error);
        alert("Error creating restaurant! Please check your input data and try again.");
    }
}

function goBack() {
    window.location.href = "index.html";
}