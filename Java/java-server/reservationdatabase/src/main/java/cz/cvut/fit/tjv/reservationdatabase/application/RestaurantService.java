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

import java.util.List;

@Service
@Transactional
public class RestaurantService implements RestaurantServiceInterface {

    private RestaurantRepository restaurantRepository;

    private CustomerRepository customerRepository;

    private CuisineRepository cuisineRepository;

    public RestaurantService (RestaurantRepository restaurantRepository, CuisineRepository cuisineRepository, CustomerRepository customerRepository) {
        this.restaurantRepository = restaurantRepository;
        this.cuisineRepository = cuisineRepository;
        this.customerRepository = customerRepository;
    }

    /**
     * Retrieves a restaurant from the database based on its unique id.
     *
     * @param id The unique id of the restaurant.
     * @return The {@link Restaurant} object associated with the given id.
     * @throws EntityNotFoundException If the restaurant with given id doesn't exist.
     */
    @Override
    public Restaurant getRestaurantById(Long id) throws EntityNotFoundException {
        return restaurantRepository.findById(id).orElseThrow(()->new EntityNotFoundException("Restaurant with id: " + id + " doesn't exist!"));
    }

    /**
     * Retrieves all restaurants from the database.
     *
     * @return A list of all {@link Restaurant} objects.
     */
    @Override
    public List<Restaurant> getRestaurants() {
        return restaurantRepository.findAll();
    }

    /**
     * Retrieves a restaurant based on its unique name.
     *
     * @param name The unique name of the restaurant.
     * @return The {@link Restaurant} object associated with the given name.
     * @throws EntityNotFoundException If the restaurant with given name doesn't exist;
     */
    @Override
    public Restaurant getRestaurantByName(String name) throws EntityNotFoundException {
        Restaurant restaurant = restaurantRepository.findRestaurantByName(name);
        if (restaurant == null) {
            throw new EntityNotFoundException("Restaurant with name: " + name + " doesn't exist!");
        }
        return restaurant;
    }


    /**
     * Creates a new restaurant.
     *
     * @param restaurant The {@link Restaurant} object that is to be created.
     * @return The created {@link Restaurant} object.
     * @throws IllegalArgumentException If the phone number of the restaurant is too short. (the phone number must be 9 characters long)
     */
    @Override
    public Restaurant createRestaurant(Restaurant restaurant) throws IllegalArgumentException {
        // Check if no other restaurant with given restaurants name exists
        if (restaurantRepository.findRestaurantByName(restaurant.getName()) == null) {
            // Check if the phone number of the restaurant is valid before saving the restaurant
            if (isValidPhoneNumber(restaurant.getPhoneNumber())) {
                // Save restaurant to the database using the repository
                return restaurantRepository.save(restaurant);
            } else {
                // If the phone number is too short, throw an IllegalArgumentException
                throw new IllegalArgumentException("The phone number: " + restaurant.getPhoneNumber() + " is too short!");
            }
        } else {
            // If another restaurant with given restaurants name already exists
            throw new IllegalArgumentException("A restaurant with name: " + restaurant.getName() + " already exists!");
        }
    }

    /**
     * Validates phone number.
     *
     * @param phoneNumber The phone number to be validated.
     * @return True if the phone number is valid, false if the phone number is invalid.
     */
    private boolean isValidPhoneNumber (String phoneNumber) {
        return (phoneNumber.length() == 9);
    }

    /**
     * Updates existing restaurant.
     *
     * @param restaurant The {@link Restaurant} object that is to be updated.
     * @return The updated {@link Restaurant} object.
     * @throws IllegalArgumentException If the restaurant doesn't exist.
     */
    @Override
    public Restaurant updateRestaurant(Restaurant restaurant) throws IllegalArgumentException {
        // Check if restaurant exists
        if (restaurantRepository.existsById(restaurant.getRestaurantId())){
            // Check if phone number is valid
            if(isValidPhoneNumber(restaurant.getPhoneNumber())) {
                // Save restaurant to the database using the repository
                return restaurantRepository.save(restaurant);
            }
            // If phone number is invalid
            throw new IllegalArgumentException("Restaurant's phone number: " + restaurant.getPhoneNumber() + " isn't valid!");
        }
        // If restaurant doesn't exist
        throw new IllegalArgumentException("Restaurant with id: " + restaurant.getRestaurantId() + " doesn't exist!");
    }

    /**
     * Deletes restaurant with given unique id.
     *
     * @param id The unique id of the restaurant.
     * @throws EntityNotFoundException If the restaurant doesn't exist.
     */
    @Override
    public void deleteRestaurant(Long id) throws EntityNotFoundException {
        // Check if restaurant exists
        if (restaurantRepository.existsById(id)) {

            Restaurant restaurantToDelete = restaurantRepository.getReferenceById(id);

            // Removes all restaurants from customer's visited restaurants that were the given restaurant
            List<Customer> customers = customerRepository.findAll();
            for (Customer customer : customers) {
                if (customer.getVisited().contains(restaurantToDelete)) {
                    customer.getVisited().remove(restaurantToDelete);
                }
            }

            // Delete restaurant from the database using the repository
            restaurantRepository.deleteById(id);
        } else {
            // If restaurant doesn't exist
            throw new EntityNotFoundException("Restaurant with id: " + id + " doesn't exist!");
        }
    }

    /**
     * Assigns cuisine with given unique id to a restaurant with given unique id.
     *
     * @param cuisineId The unique id of the cuisine.
     * @param restaurantId The unique id of the restaurant.
     * @return The {@link Restaurant} object with a cuisine assigned to it.
     * @throws IllegalArgumentException If cuisine or restaurant don't exist.
     */
    @Override
    public Restaurant addCuisineToRestaurant(Long cuisineId, Long restaurantId) throws IllegalArgumentException {
        // Check if restaurant exists
        if (restaurantRepository.existsById(restaurantId)) {
            // Check if cuisine exists
            if (cuisineRepository.existsById(cuisineId)) {
                // Get reference to restaurant
                Restaurant rest = restaurantRepository.getReferenceById(restaurantId);
                // Set cuisine of restaurant to specific cuisine
                rest.setCooks(cuisineRepository.getReferenceById(cuisineId));
                return rest;
            } else {
                // If cuisine doesn't exist
                throw new IllegalArgumentException("Cuisine with id: " + cuisineId + " doesn't exist!");
            }
        } else {
            //If restaurant doesn't exist
            throw new IllegalArgumentException("Restaurant with id: " + restaurantId + " doesn't exist!");
        }
    }

    /**
     * Removes cuisine from restaurant with given unique id.
     *
     * @param restaurantId The restaurant unique id.
     * @return The {@link Restaurant} object with removed cuisine.
     * @throws IllegalArgumentException If restaurant doesn't exist.
     */
    @Override
    public Restaurant removeCuisineFromRestaurant(Long restaurantId) throws IllegalArgumentException {
        // Check if restaurant exists
        if (restaurantRepository.existsById(restaurantId)) {
            // Get reference to restaurant
            Restaurant rest = restaurantRepository.getReferenceById(restaurantId);
            // Set cuisine of restaurant to null
            rest.setCooks(null);
            return rest;
        }
        // If restaurant doesn't exist
        throw new IllegalArgumentException("Restaurant with id: " + restaurantId + " doesn't exist!");
    }


}
