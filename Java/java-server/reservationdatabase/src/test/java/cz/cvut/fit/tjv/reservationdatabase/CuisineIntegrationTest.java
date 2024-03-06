package cz.cvut.fit.tjv.reservationdatabase;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineService;
import cz.cvut.fit.tjv.reservationdatabase.controller.CuisineController;
import cz.cvut.fit.tjv.reservationdatabase.controller.converter.CuisineDTOConverter;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.persistent.CuisineRepository;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;
import org.springframework.web.server.ResponseStatusException;

import static org.junit.jupiter.api.Assertions.assertThrows;

@SpringBootTest()
@AutoConfigureMockMvc
public class CuisineIntegrationTest {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private CuisineRepository cuisineRepository;

    @Test
    public void testCreateCuisine() throws Exception {
        String cuisineJson = "{" +
                "\"country\": \"Zimbabwe\"" +
                "}";

        mockMvc.perform(MockMvcRequestBuilders.post("/rest/api/cuisine")
                .contentType(MediaType.APPLICATION_JSON)
                .content(cuisineJson))
                .andDo(MockMvcResultHandlers.print())
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andExpect(MockMvcResultMatchers.jsonPath("$.country", Matchers.is("Zimbabwe")));

        mockMvc.perform(MockMvcRequestBuilders.post("/rest/api/cuisine")
                .contentType(MediaType.APPLICATION_JSON)
                .content(cuisineJson)).andExpect(MockMvcResultMatchers.status().isBadRequest());

        Cuisine createdCuisine = cuisineRepository.findCuisineByCountry("Zimbabwe");
        if (createdCuisine != null) {
            cuisineRepository.delete(createdCuisine);
        }
    }

}
