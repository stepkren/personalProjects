package cz.cvut.fit.tjv.reservationdatabase.application;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import jakarta.persistence.EntityExistsException;
import jakarta.persistence.EntityNotFoundException;

import java.util.List;

public interface CustomerServiceInterface {
    public Customer getCustomerById(Long id) throws EntityNotFoundException;

    public List<Customer> getCustomers();

    public Customer getCustomerByName (String name) throws EntityNotFoundException;

    public List<Customer> findCustomerThatVisitedRestaurantCookingCuisine (Cuisine cuisine) throws IllegalArgumentException;

    public Customer createCustomer(Customer customer) throws IllegalArgumentException;

    public Customer updateCustomer(Customer customer) throws IllegalArgumentException;

    public void deleteCustomer(Long id) throws EntityNotFoundException;

    public void addRestaurantToCustomer (Long restaurantId, Long customerId) throws EntityNotFoundException, IllegalArgumentException;

    public void removeRestaurantFromCustomer (Long restaurantId, Long customerId) throws EntityNotFoundException, IllegalArgumentException;
}
