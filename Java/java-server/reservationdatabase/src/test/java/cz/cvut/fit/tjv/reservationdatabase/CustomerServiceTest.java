package cz.cvut.fit.tjv.reservationdatabase;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineService;
import cz.cvut.fit.tjv.reservationdatabase.application.CustomerService;
import cz.cvut.fit.tjv.reservationdatabase.application.RestaurantService;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CuisineRepository;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CustomerRepository;
import cz.cvut.fit.tjv.reservationdatabase.persistent.RestaurantRepository;
import jakarta.persistence.EntityNotFoundException;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@SpringBootTest
public class CustomerServiceTest {

    @Mock
    private CustomerRepository customerRepository;

    @Mock
    private RestaurantRepository restaurantRepository;

    @Mock
    private CuisineRepository cuisineRepository;

    @InjectMocks
    private CustomerService customerService;

    @InjectMocks
    private CuisineService cuisineService;

    @Test
    public void testCreateCustomer() {
        Customer testCustomer = new Customer();
        testCustomer.setName("Albus Dumbledore");
        testCustomer.setPhoneNumber("123456789");
        testCustomer.setEmail("brumbal@hogwarts.wz");

        when(customerRepository.findCustomerByName(testCustomer.getName())).thenReturn(null);
        when(customerRepository.save(testCustomer)).thenReturn(testCustomer);

        Customer createdCustomer = assertDoesNotThrow(() -> customerService.createCustomer(testCustomer));

        assertNotNull(createdCustomer);
        assertEquals(testCustomer, createdCustomer);
    }

    @Test
    public void testCreateCustomerWithExistingName() {
        Customer existingCustomer = new Customer();
        existingCustomer.setName("Sylvester Stallone");

        Customer testCustomer = new Customer();
        testCustomer.setName("Sylvester Stallone");
        testCustomer.setPhoneNumber("987654321");
        testCustomer.setEmail("silvestr@novyrok.cz");

        when(customerRepository.findCustomerByName(existingCustomer.getName())).thenReturn(existingCustomer);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> customerService.createCustomer(testCustomer));

        assertEquals("Customer with name: Sylvester Stallone already exists!", exception.getMessage());
    }

    @Test
    public void testCreateCustomerWithInvalidPhoneNumber() {
        Customer testCustomer = new Customer();
        testCustomer.setName("Bill Gates");
        testCustomer.setPhoneNumber("123456");
        testCustomer.setEmail("bill.gates@gmail.com");

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> customerService.createCustomer(testCustomer));

        assertEquals("Customer's phone number isn't a valid phone number!", exception.getMessage());
        verify(customerRepository, never()).save(any());
    }

    @Test
    public void testCreateCustomerWithInvalidEmail() {
        Customer testCustomer = new Customer();
        testCustomer.setName("Bill Gates");
        testCustomer.setPhoneNumber("123456789");
        testCustomer.setEmail("billgejts");

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> customerService.createCustomer(testCustomer));

        assertEquals("Customer's email address isn't a valid email address!", exception.getMessage());
        verify(customerRepository, never()).save(any());
    }

    @Test
    public void testAddRestaurantToCustomer() {
        Long customerId = 1L;
        Long restaurantId = 2L;

        Customer testCustomer = new Customer();
        testCustomer.setCustomerId(customerId);
        testCustomer.setVisited(new ArrayList<>());
        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setRestaurantId(restaurantId);
        testRestaurant.setOpenFrom(new Date(System.currentTimeMillis() - 1000));

        when(customerRepository.existsById(customerId)).thenReturn(true);
        when(restaurantRepository.existsById(restaurantId)).thenReturn(true);
        when(customerRepository.getReferenceById(customerId)).thenReturn(testCustomer);
        when(restaurantRepository.getReferenceById(restaurantId)).thenReturn(testRestaurant);
        when(customerRepository.save(any())).thenReturn(testCustomer);

        assertDoesNotThrow(() -> customerService.addRestaurantToCustomer(restaurantId, customerId));

        assertTrue(testCustomer.getVisited().contains(testRestaurant));
    }

    @Test
    void testAddRestaurantToCustomerWithNonExistingRestaurant() {
        Long customerId = 1L;
        Long restaurantId = 2L;

        Customer testCustomer = new Customer();
        testCustomer.setCustomerId(customerId);
        testCustomer.setVisited(new ArrayList<>());

        when(customerRepository.existsById(customerId)).thenReturn(true);
        when(restaurantRepository.existsById(restaurantId)).thenReturn(false);

        EntityNotFoundException exception = assertThrows(EntityNotFoundException.class, () -> customerService.addRestaurantToCustomer(restaurantId, customerId));

        assertEquals("Restaurant with id: 2 doesn't exist!", exception.getMessage());
    }

    @Test
    void testAddRestaurantToCustomerNotYetOpenRestaurant() {
        Long customerId = 1L;
        Long restaurantId = 2L;

        Customer testCustomer = new Customer();
        testCustomer.setCustomerId(customerId);
        testCustomer.setVisited(new ArrayList<>());
        Restaurant testRestaurant = new Restaurant();
        testRestaurant.setRestaurantId(restaurantId);
        testRestaurant.setOpenFrom(new Date(System.currentTimeMillis() + 100000));

        when(customerRepository.existsById(customerId)).thenReturn(true);
        when(restaurantRepository.existsById(restaurantId)).thenReturn(true);
        when(customerRepository.getReferenceById(customerId)).thenReturn(testCustomer);
        when(restaurantRepository.getReferenceById(restaurantId)).thenReturn(testRestaurant);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> customerService.addRestaurantToCustomer(restaurantId, customerId));

        assertEquals("Restaurant with id: 2 isn't yet open!", exception.getMessage());

        assertFalse(testCustomer.getVisited().contains(testRestaurant));
    }

    @Test
    public void testJPQLQuery() {
        Cuisine testCuisine = new Cuisine();
        testCuisine.setCuisineId(1L);
        testCuisine.setCountry("Turkey");

        Cuisine tmpCuisine = new Cuisine();
        tmpCuisine.setCuisineId(5L);
        tmpCuisine.setCountry("Island");

        Restaurant testRestaurantWithTestCuisine = new Restaurant();
        testRestaurantWithTestCuisine.setRestaurantId(3L);
        testRestaurantWithTestCuisine.setCooks(testCuisine);

        Restaurant testRestaurantWithDifferentCuisine = new Restaurant();
        testRestaurantWithDifferentCuisine.setRestaurantId(4L);
        testRestaurantWithDifferentCuisine.setCooks(tmpCuisine);

        Customer testCustomer1 = new Customer();
        testCustomer1.setVisited(List.of(testRestaurantWithTestCuisine, testRestaurantWithDifferentCuisine));

        Customer testCustomer2 = new Customer();
        testCustomer2.setVisited(List.of(testRestaurantWithTestCuisine));

        Customer testCustomer3 = new Customer();
        testCustomer3.setVisited(List.of(testRestaurantWithDifferentCuisine));

        when(cuisineRepository.existsById(testCuisine.getCuisineId())).thenReturn(true);
        when(customerRepository.findCustomerThatVisitedRestaurantCookingCuisine(testCuisine))
                .thenReturn(List.of(testCustomer1, testCustomer2));

        List<Customer> result = assertDoesNotThrow(() -> customerService.findCustomerThatVisitedRestaurantCookingCuisine(testCuisine));

        assertNotNull(result);
        assertEquals(2, result.size());
    }
}
