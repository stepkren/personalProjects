package cz.cvut.fit.tjv.reservationdatabase;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineService;
import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantService;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CuisineRepository;
import cz.cvut.fit.tjv.reservationdatabase.persistent.RestaurantRepository;
import jakarta.persistence.EntityNotFoundException;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.sql.Date;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@SpringBootTest
public class RestaurantServiceTest {
    @Mock
    private RestaurantRepository restaurantRepository;

    @Mock
    private CuisineRepository cuisineRepository;

    @InjectMocks
    private RestaurantService restaurantService;

    @InjectMocks
    private CuisineService cuisineService;

    @Test
    public void testCreateRestaurant() {
       Restaurant testRestaurant = new Restaurant();
       testRestaurant.setName("U Dvou slunců");
       testRestaurant.setPhoneNumber("123456789");
       testRestaurant.setOpenFrom(new Date(2023, 6, 25));
       testRestaurant.setItemsOnMenu(15L);

       when(restaurantRepository.findRestaurantByName(testRestaurant.getName())).thenReturn(null);
       when(restaurantRepository.save(testRestaurant)).thenReturn(testRestaurant);

       Restaurant createdRestaurant = assertDoesNotThrow(() -> restaurantService.createRestaurant(testRestaurant));

       assertNotNull(createdRestaurant);
       assertEquals(testRestaurant, createdRestaurant);
    }

    @Test
    public void testCreateRestaurantWithExistingName() {
        Restaurant existingRestaurant = new Restaurant();
        existingRestaurant.setName("U Zlatého lva");

        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setName("U Zlatého lva");
        testRestaurant.setPhoneNumber("123456789");
        testRestaurant.setOpenFrom(new Date(2023, 6, 25));
        testRestaurant.setItemsOnMenu(15L);

        when(restaurantRepository.findRestaurantByName(existingRestaurant.getName())).thenReturn(existingRestaurant);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class ,() -> restaurantService.createRestaurant(testRestaurant));

        assertEquals("A restaurant with name: U Zlatého lva already exists!", exception.getMessage());
    }

    @Test
    public void testCreateRestaurantWithInvalidPhoneNumber() {
        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setName("Vila u Varhanáře");
        testRestaurant.setPhoneNumber("123456789+");
        testRestaurant.setOpenFrom(new Date(2023, 6, 25));
        testRestaurant.setItemsOnMenu(15L);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> restaurantService.createRestaurant(testRestaurant));

        assertEquals("The phone number: " + testRestaurant.getPhoneNumber() + " is too short!", exception.getMessage());
        verify(restaurantRepository, never()).save(any());
    }

    @Test
    public void testAddCuisineToRestaurant() {
        Long cuisineId = 1L;
        Long restaurantId = 2L;

        Cuisine testCuisine = new Cuisine();
        testCuisine.setCuisineId(cuisineId);
        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setRestaurantId(restaurantId);

        when(restaurantRepository.existsById(restaurantId)).thenReturn(true);
        when(cuisineRepository.existsById(cuisineId)).thenReturn(true);
        when(restaurantRepository.getReferenceById(restaurantId)).thenReturn(testRestaurant);
        when(cuisineRepository.getReferenceById(cuisineId)).thenReturn(testCuisine);

        Restaurant result = restaurantService.addCuisineToRestaurant(cuisineId, restaurantId);

        assertEquals(testCuisine, testRestaurant.getCooks());
        assertEquals(testRestaurant, result);
    }


    @Test
    public void testAddCuisineToRestaurantWithNonExistingCuisine() {
        Long cuisineId = 1L;
        Long restaurantId = 2L;

        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setRestaurantId(restaurantId);

        when(restaurantRepository.existsById(restaurantId)).thenReturn(true);
        when(cuisineRepository.existsById(cuisineId)).thenReturn(false);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> restaurantService.addCuisineToRestaurant(cuisineId, restaurantId));

        assertEquals("Cuisine with id: " + cuisineId + " doesn't exist!", exception.getMessage());
    }

    @Test
    public void testRemoveCuisineFromRestaurant() {
        Long restaurantId = 1L;

        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setCooks(new Cuisine());

        when(restaurantRepository.existsById(restaurantId)).thenReturn(true);
        when(restaurantRepository.getReferenceById(restaurantId)).thenReturn(testRestaurant);

        Restaurant result = restaurantService.removeCuisineFromRestaurant(restaurantId);

        assertNull(testRestaurant.getCooks());
        assertEquals(testRestaurant, result);
    }

    @Test
    public void testRemoveCuisineFromNonExistingRestaurant() {
        Long restaurantId = 1L;

        when(restaurantRepository.existsById(restaurantId)).thenReturn(false);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> restaurantService.removeCuisineFromRestaurant(restaurantId));

        assertEquals("Restaurant with id: " + restaurantId + " doesn't exist!", exception.getMessage());
    }
}
