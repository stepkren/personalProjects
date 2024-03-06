package cz.cvut.fit.tjv.reservationdatabase.application;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import jakarta.persistence.EntityExistsException;
import jakarta.persistence.EntityNotFoundException;

import java.util.List;

public interface RestaurantServiceInterface {
    public Restaurant getRestaurantById (Long id) throws EntityNotFoundException;

    public List<Restaurant> getRestaurants ();

    public Restaurant getRestaurantByName(String name) throws EntityNotFoundException;

    public Restaurant createRestaurant (Restaurant restaurant) throws IllegalArgumentException;

    public Restaurant updateRestaurant (Restaurant restaurant) throws IllegalArgumentException;

    public void deleteRestaurant (Long id) throws EntityNotFoundException;

    public Restaurant addCuisineToRestaurant (Long cuisineId, Long restaurantId) throws IllegalArgumentException;

    public Restaurant removeCuisineFromRestaurant (Long restaurantId) throws IllegalArgumentException;
}
