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

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

@Service
@Transactional
public class CuisineService implements CuisineServiceInterface {

    private CuisineRepository cuisineRepository;

    private CustomerRepository customerRepository;

    private RestaurantRepository restaurantRepository;

    private RestaurantService restaurantService;

    public CuisineService(CuisineRepository cuisineRepository, CustomerRepository customerRepository, RestaurantRepository restaurantRepository, RestaurantService restaurantService){
        this.cuisineRepository = cuisineRepository;
        this.customerRepository = customerRepository;
        this.restaurantRepository = restaurantRepository;
        this.restaurantService = restaurantService;
    }

    /**
     * Retrieves cuisine from the database based on its unique id
     *
     * @param id The cuisines unique id.
     * @return The {@link Cuisine} object associated with the given id.
     * @throws EntityNotFoundException If cuisine doesn't exist.
     */
    @Override
    public Cuisine getCuisineById(Long id) throws EntityNotFoundException {
        return cuisineRepository.findById(id).orElseThrow(()->new EntityNotFoundException("Cuisine with id: " + id + " not found!"));
    }

    /**
     * Retrieves all cuisines.
     *
     * @return A list of all {@link Cuisine} objects.
     */
    @Override
    public List<Cuisine> getCuisines() {
        return cuisineRepository.findAll();
    }

    /**
     * Retrieves cuisine based on its unique country.
     *
     * @param country The unique country of the cuisine.
     * @return The {@link Cuisine} object associated with the given country.
     * @throws EntityNotFoundException If cuisine with given country doesn't exist.
     */
    @Override
    public Cuisine getCuisineByCountry(String country) throws EntityNotFoundException {
        Cuisine cuisine = cuisineRepository.findCuisineByCountry(country);
        if (cuisine == null) {
            throw new EntityNotFoundException("Cuisine with country: " + country + " doesn't exist.");
        }
        return cuisine;
    }


    /**
     * Creates a new cuisine.
     *
     * @param cuisine The {@link Cuisine} object that is to be created.
     * @return The created {@link Cuisine} object.
     * @throws IllegalArgumentException If country is invalid.
     */
    @Override
    public Cuisine createCuisine(Cuisine cuisine) throws IllegalArgumentException {
        // Check if there already is a cuisine with given cuisines country
        if (cuisineRepository.findCuisineByCountry(cuisine.getCountry()) == null) {
            // Check if the country of the cuisine is valid
            if (isValidCountry(cuisine.getCountry())) {
                // Save cuisine to the database using the repository
                return cuisineRepository.save(cuisine);
            } else {
                // If country is invalid
                throw new IllegalArgumentException("The country is invalid!");
            }
        } else {
            // If cuisine with country already exists
            throw new IllegalArgumentException("A cuisine with country: " + cuisine.getCountry() + " already exists!");
        }
    }

    /**
     * Validates country.
     *
     * @param country The country that is to be validated.
     * @return True if country is valid, false if country is invalid.
     */
    private boolean isValidCountry (String country) {
        // Matches country to a pattern (must start with capital letter, after that can only contain letters and spaces)
        return country.matches("[A-Z][a-zA-Z ]*");
    }

    /**
     * Updates existing cuisine.
     *
     * @param cuisine The {@link Cuisine} object that is to be updated.
     * @return The updated {@link Cuisine} object.
     * @throws IllegalArgumentException If cuisine doesn't exist.
     */
    @Override
    public Cuisine updateCuisine(Cuisine cuisine) throws IllegalArgumentException {
        // Check if cuisine exists
        if (cuisineRepository.existsById(cuisine.getCuisineId())){
            // Check if country is valid
            if(isValidCountry(cuisine.getCountry())) {
                // Save cuisine to the database using the repository
                return cuisineRepository.save(cuisine);
            }
            // If cuisine country isn't valid
            throw new IllegalArgumentException("Cuisine country: " + cuisine.getCountry() + " isn't valid!");
        }
        // If cuisine doesn't exist
        throw new IllegalArgumentException("Cuisine with id: " + cuisine.getCuisineId() + " doesn't exist!");
    }

    /**
     * Deletes cuisine with given unique id.
     *
     * @param id The unique id of the cuisine.
     * @throws EntityNotFoundException If cuisine doesn't exist.
     */
    @Override
    public void deleteCuisine(Long id) throws EntityNotFoundException {
        // Check if cuisine exists
        if (cuisineRepository.existsById(id)){
            List<Restaurant> restaurantsAll = restaurantRepository.findAll();
            List<Restaurant> restaurantsToDelete = Collections.emptyList();

            // Removes all restaurants from the visited restaurants of a customer that cooked given cuisine
            List<Customer> customers = customerRepository.findAll();
            for (Customer customer : customers) {
                List<Restaurant> restaurants = customer.getVisited();
                if (customer.getVisited() == null) {
                    restaurants = Collections.emptyList();
                }
                Iterator<Restaurant> iterator = restaurants.iterator();
                while(iterator.hasNext()) {
                    Restaurant restaurant = iterator.next();
                    if (restaurant.getCooks().getCuisineId().equals(id)) {
                        iterator.remove();
                    }
                }
            }

            // Delete all restaurants that cooked given cuisine
            for (Restaurant restaurant : restaurantsAll) {
                if (restaurant.getCooks().getCuisineId().equals(id)) {
                    restaurantService.deleteRestaurant(restaurant.getRestaurantId());
                }
            }

            // Delete cuisine from the database using the repository
            cuisineRepository.deleteById(id);
        } else {
            // If cuisine doesn't exist
            throw new EntityNotFoundException("Cuisine with id: " + id + " doesn't exist!");
        }
    }
}
