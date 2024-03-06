package cz.cvut.fit.tjv.reservationdatabase.application;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import jakarta.persistence.EntityExistsException;
import jakarta.persistence.EntityNotFoundException;

import java.util.List;

public interface CuisineServiceInterface {
    public Cuisine getCuisineById (Long id) throws EntityNotFoundException;

    public List<Cuisine> getCuisines ();

    public Cuisine getCuisineByCountry (String cuisine) throws EntityNotFoundException;

    public Cuisine createCuisine (Cuisine cuisine) throws IllegalArgumentException;

    public Cuisine updateCuisine (Cuisine cuisine) throws IllegalArgumentException;

    public void deleteCuisine (Long id) throws EntityNotFoundException;
}
