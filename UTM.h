//
// Created by USUARIO on 11/12/2025.
//

#ifndef P6_UTM_H
#define P6_UTM_H


class UTM {
private:
    float longitud;
    float latitud;
public:
    UTM();
    UTM(float latitud, float longitud);
    UTM(const UTM& orig);

    float getLongitud() const;
    void setLongitud(float longitud);

    float getLatitud() const;
    void setLatitud(float latitud);

    virtual ~UTM();
};


#endif //P6_UTM_H
