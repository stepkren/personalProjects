function goBack() {
    window.location.href = "index.html";
}

async function findCustomers() {
    try {
        console.log(cuisineId);
        const response = await fetch(`http://localhost:8080/rest/api/customer/specific?cu=${cuisineId}`);
        const customers = await response.json();

        const customerList = document.getElementById("customerList");

        customers.forEach(customer => {
           const customerDiv = document.createElement('div');
           customerDiv.innerHTML = `
                <p>ID: ${customer.customerId}, ${customer.name}, Email: ${customer.email}, Tel.: ${customer.phoneNumber}</p>
                <hr>
           `;
           customerList.appendChild(customerDiv);
        });

    } catch (error) {
        console.error('Error fetching customers.', error);
    }
}

const urlParams = new URLSearchParams(window.location.search);
const cuisineId = urlParams.get('cuisineId');
if (cuisineId) {
    console.log(`ID: ${cuisineId}`);
} else {
    console.error('Cuisines ID not provided in the url');
}

window.onload = findCustomers;