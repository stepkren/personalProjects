package cz.cvut.fit.tjv.reservationdatabase.application;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CuisineRepository;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CustomerRepository;
import cz.cvut.fit.tjv.reservationdatabase.persistent.RestaurantRepository;
import jakarta.persistence.EntityNotFoundException;
import jakarta.transaction.Transactional;
import org.springframework.stereotype.Service;

import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.regex.Pattern;


@Service
@Transactional
public class CustomerService implements CustomerServiceInterface {

    private CustomerRepository customerRepository;
    private CuisineRepository cuisineRepository;
    private RestaurantRepository restaurantRepository;

    public CustomerService(CustomerRepository customerRepository, CuisineRepository cuisineRepository, RestaurantRepository restaurantRepository){
        this.customerRepository = customerRepository;
        this.cuisineRepository = cuisineRepository;
        this.restaurantRepository = restaurantRepository;
    }

    /**
     * Retrieves a customer from the database based on its unique id.
     *
     * @param id The unique id of the customer.
     * @return The {@link Customer} object associated with the given id.
     * @throws EntityNotFoundException If customer doesn't exist.
     */
    @Override
    public Customer getCustomerById(Long id) throws EntityNotFoundException {
        return customerRepository.findById(id).orElseThrow(()->new EntityNotFoundException("Customer with id: " + id + " not found!"));
    }

    /**
     * Retrieves all customers from the database.
     *
     * @return A list of all {@link Customer} objects.
     */
    @Override
    public List<Customer> getCustomers() {
        return customerRepository.findAll();
    }

    /**
     * Retrieves a customer based on its unique name.
     *
     * @param name The customers unique name.
     * @return The {@link Customer} object associated with the given name.
     * @throws EntityNotFoundException If customer with given name doesn't exist.
     */
    @Override
    public Customer getCustomerByName(String name) throws EntityNotFoundException {
        Customer customer = customerRepository.findCustomerByName(name);
        if (customer == null) {
            throw new EntityNotFoundException("Customer with name: " + name + " doesn't exist!");
        }
        return customer;
    }

    /**
     * Retrieves all customers that visited a restaurant cooking a specific cuisine.
     *
     * @param cuisine The {@link Cuisine} object that is to be cooked at the restaurant.
     * @return A list of {@link Customer} objects that who meet the conditions.
     * @throws IllegalArgumentException If cuisine doesn't exist.
     */
    @Override
    public List<Customer> findCustomerThatVisitedRestaurantCookingCuisine(Cuisine cuisine) throws IllegalArgumentException {
        // Check if cuisine exists
        if (cuisineRepository.existsById(cuisine.getCuisineId())) {
            // Calls JPQL query returning a list of customers
            return customerRepository.findCustomerThatVisitedRestaurantCookingCuisine(cuisine);
        }
        // If cuisine doesn't exist
        throw new IllegalArgumentException("Cuisine with id: " + cuisine.getCuisineId() + " doesn't exist!");
    }



    /**
     * Creates a new customer.
     *
     * @param customer The {@link Customer} object that is to be created.
     * @return The created {@link Customer} object.
     * @throws IllegalArgumentException If customers phone number or email address are invalid.
     */
    @Override
    public Customer createCustomer(Customer customer) throws IllegalArgumentException {
        // Check if there is no other customer with given customer name
        if (customerRepository.findCustomerByName(customer.getName()) == null) {
            // Check if phone number is valid
            if (isValidPhoneNumber(customer.getPhoneNumber())) {
                // Check if email address is valid
                if (isValidEmailAddress(customer.getEmail())) {
                    // Save customer to the database using the repository
                    return customerRepository.save(customer);
                } else {
                    // If email address is invalid
                    throw new IllegalArgumentException("Customer's email address isn't a valid email address!");
                }
            } else {
                // If phone number is invalid
                throw new IllegalArgumentException("Customer's phone number isn't a valid phone number!");
            }
        } else {
            // If another customer with given customers name already exists
            throw new IllegalArgumentException("Customer with name: " + customer.getName() + " already exists!");
        }
    }

    /**
     * Validates phone number.
     *
     * @param phoneNumber The phone number to be validated.
     * @return True if the phone number is valid, false if the phone number is invalid.
     */
    private boolean  isValidPhoneNumber (String phoneNumber) {
        return phoneNumber.length() == 9;
    }

    /**
     * Validates email address.
     *
     * @param emailAddress The email address to be validated.
     * @return True if the email address is valid, false if the email address is invalid.
     */
    private boolean isValidEmailAddress (String emailAddress) {
        // Matches email address to pattern
        return emailAddress.matches("^[a-zA-Z0-9]+@[a-z]+\\.[a-z]+$");
    }

    /**
     * Updates existing customer.
     *
     * @param customer The {@link Customer} object that is to be updated.
     * @return The updated {@link Customer} object.
     * @throws IllegalArgumentException If customer doesn't exist.
     */
    @Override
    public Customer updateCustomer(Customer customer) throws IllegalArgumentException {
        // Check if customer exists
        if (customerRepository.existsById(customer.getCustomerId())) {
            // Check if phone number is valid
            if(isValidPhoneNumber(customer.getPhoneNumber())) {
                // Check if email address is valid
                if(isValidEmailAddress(customer.getEmail())) {
                    // Save customer to the database using the repository
                    return customerRepository.save(customer);
                } else {
                    // If email address is invalid
                    throw new IllegalArgumentException("Customer's email address: " + customer.getEmail() + " isn't valid!");
                }
            } else {
                // If phone number is invalid
                throw new IllegalArgumentException("Customer's phone number: " + customer.getPhoneNumber() + " isn't valid!");
            }
        } else {
            // If customer doesn't exist
            throw new IllegalArgumentException("Customer with id: " + customer.getCustomerId() + " doesn't exist!");
        }
    }

    /**
     * Deletes customer with given unique id.
     *
     * @param id The unique id of the customer.
     * @throws EntityNotFoundException If customer doesn't exit.
     */
    @Override
    public void deleteCustomer(Long id) throws EntityNotFoundException {
        // Check if customer exists
        if (customerRepository.existsById(id)) {
            // Delete customer from the database using the repository
            customerRepository.deleteById(id);
        } else {
            // If customer doesn't exist
            throw new EntityNotFoundException("Customer with id: " + id + " doesn't exist!");
        }
    }

    /**
     * Adds restaurant to list of customer's visited restaurants.
     *
     * @param restaurantId The unique id of the restaurant.
     * @param customerId The unique id of the customer.
     * @throws EntityNotFoundException If restaurant or customer don't exist.
     * @throws IllegalArgumentException If restaurant isn't yet open.
     */
    @Override
    public void addRestaurantToCustomer(Long restaurantId, Long customerId) throws EntityNotFoundException, IllegalArgumentException {
        // Check if customer exists
        if (customerRepository.existsById(customerId)) {
            // Check if restaurant exists
            if (restaurantRepository.existsById(restaurantId)) {
                // Get reference to restaurant
                Restaurant restaurant = restaurantRepository.getReferenceById(restaurantId);
                if (customerRepository.getReferenceById(customerId).getVisited().contains(restaurantRepository.getReferenceById(restaurantId))) {
                    throw new IllegalArgumentException("Restaurant with id: " + restaurantId + " is already in the list!");
                }
                Calendar calendar = Calendar.getInstance();
                Date currentDate = calendar.getTime();
                if (restaurant.getOpenFrom().after(currentDate)) {
                    // If restaurant isn't yet open
                    throw new IllegalArgumentException("Restaurant with id: " + restaurantId + " isn't yet open!");
                }
                // Add restaurant to list of visited restaurants of customer
                customerRepository.getReferenceById(customerId).getVisited().add(restaurantRepository.getReferenceById(restaurantId));
                return;
            } else {
                // If restaurant doesn't exist
                throw new EntityNotFoundException("Restaurant with id: " + restaurantId + " doesn't exist!");
            }
        } else {
            // If customer doesn't exist
            throw new EntityNotFoundException("Customer with id: " + customerId + " doesn't exist!");
        }
    }

    /**
     * Removes restaurant from list of customer's visited restaurants.
     *
     * @param restaurantId The unique id of the restaurant.
     * @param customerId The unique id of the customer.
     * @throws EntityNotFoundException If restaurant or customer don't exist.
     * @throws IllegalArgumentException If customer didn't visit the restaurant.
     */
    @Override
    public void removeRestaurantFromCustomer(Long restaurantId, Long customerId) throws EntityNotFoundException, IllegalArgumentException {
        // Check if customer exists
        if (customerRepository.existsById(customerId)) {
            // Check if restaurant exists
            if (restaurantRepository.existsById(restaurantId)) {
                // Get reference to customer and restaurant
                Customer customer = customerRepository.getReferenceById(customerId);
                Restaurant restaurant = restaurantRepository.getReferenceById(restaurantId);

                // Check if customer visited restaurant
                if (customer.getVisited().contains(restaurant)) {
                    // Remove restaurant from list of visited restaurants
                    customer.getVisited().remove(restaurant);
                    return;
                } else {
                    // If customer didn't visit restaurant
                    throw new IllegalArgumentException("Customer with id: " + customerId + " didn't visit restaurant with id: " + restaurantId + "!");
                }
            } else {
                // If restaurant doesn't exist
                throw new EntityNotFoundException("Restaurant with id: " + restaurantId + " doesn't exist!");
            }
        } else {
            // If customer doesn't exist
            throw new EntityNotFoundException("Customer with id: " + customerId + " doesn't exist!");
        }
    }


}
