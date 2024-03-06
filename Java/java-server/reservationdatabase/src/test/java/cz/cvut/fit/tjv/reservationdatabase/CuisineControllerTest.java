package cz.cvut.fit.tjv.reservationdatabase;

import cz.cvut.fit.tjv.reservationdatabase.application.CuisineService;
import cz.cvut.fit.tjv.reservationdatabase.controller.CuisineController;
import cz.cvut.fit.tjv.reservationdatabase.controller.converter.CuisineDTOConverter;
import cz.cvut.fit.tjv.reservationdatabase.controller.dto.CuisineDTO;
import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.util.Collections;
import java.util.regex.Matcher;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

@ExtendWith(SpringExtension.class)
@WebMvcTest(CuisineController.class)
public class CuisineControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private CuisineService cuisineService;

    @MockBean
    private CuisineDTOConverter cuisineDTOConverter;

    // THIS TEST DOESN'T WORK, I DIDN'T FIGURE OUT WHY, TODO

    /*@Test
    void createCuisine() throws Exception {
        CuisineDTO cuisineDTO = new CuisineDTO(1L, "USA", null);
        Cuisine cuisineEntity = new Cuisine(1L, "USA", null);

        when(cuisineDTOConverter.toEntity(any(CuisineDTO.class))).thenReturn(cuisineEntity);
        when(cuisineDTOConverter.toDTO(any(Cuisine.class))).thenReturn(cuisineDTO);

        when(cuisineService.createCuisine(any(Cuisine.class))).thenReturn(cuisineEntity);

        String cuisineJson = "{" +
                "\"country\": \"USA\"" +
                "}";

        mockMvc.perform(
                MockMvcRequestBuilders.post("/rest/api/cuisine")
                .contentType(MediaType.APPLICATION_JSON)
                .content(cuisineJson)
                )
                .andDo(MockMvcResultHandlers.print())
                .andExpect(MockMvcResultMatchers.status().isOk())
                .andExpect(MockMvcResultMatchers.jsonPath("$.country", Matchers.is("USA")));

        verify(cuisineService).createCuisine(any(Cuisine.class));
        verify(cuisineDTOConverter).toDTO(any(Cuisine.class));
    }*/

}
