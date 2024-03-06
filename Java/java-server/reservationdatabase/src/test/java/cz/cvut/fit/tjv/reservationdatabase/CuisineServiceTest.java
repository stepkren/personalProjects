package cz.cvut.fit.tjv.reservationdatabase;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineService;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CuisineRepository;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.when;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
@ExtendWith(SpringExtension.class)
@SpringBootTest
public class CuisineServiceTest {

    @Mock
    private CuisineRepository cuisineRepository;

    @InjectMocks
    private CuisineService cuisineService;

    @Test
    public void testCreateCuisine() {
        Cuisine testCuisine = new Cuisine();
        testCuisine.setCountry("Turkey");

        when(cuisineRepository.findCuisineByCountry(testCuisine.getCountry())).thenReturn(null);
        when(cuisineRepository.save(testCuisine)).thenReturn(testCuisine);

        Cuisine createdCuisine = assertDoesNotThrow(() -> cuisineService.createCuisine(testCuisine));

        assertNotNull(createdCuisine);
        assertEquals(testCuisine, createdCuisine);
    }

    @Test
    public void testCreateCuisineWithExistingCountry() {
        Cuisine existingCuisine = new Cuisine();
        existingCuisine.setCountry("Romania");

        Cuisine testCuisine = new Cuisine();
        testCuisine.setCountry("Romania");

        when(cuisineRepository.findCuisineByCountry(existingCuisine.getCountry())).thenReturn(existingCuisine);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> cuisineService.createCuisine(testCuisine));

        assertEquals("A cuisine with country: " + testCuisine.getCountry() + " already exists!", exception.getMessage());
    }

    @Test
    public void testCreateCuisineWithInvalidCountry() {
        Cuisine testCuisine = new Cuisine();
        testCuisine.setCountry("Can4da");

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> cuisineService.createCuisine(testCuisine));

        assertEquals("The country is invalid!", exception.getMessage());
    }
}
