package modele;

import java.io.Serializable;
import java.util.ArrayList;

public class SvgListe implements Serializable{
    private ArrayList<Membre> aTrier;
    private boolean filterSurPaye;
    private ArrayList<String> filtrageType;
    private ArrayList<Integer> filtrageNiveau;
    private ArrayList<Integer> ordreTriage;

    




    public SvgListe(ArrayList<Membre> aTrier,boolean filterSurPaye, ArrayList<String> filtrageType ,ArrayList<Integer> filtrageNiveau,ArrayList<Integer> ordreTriage) {
        this.aTrier = aTrier;
        this.filterSurPaye = filterSurPaye;
        this.filtrageNiveau = filtrageNiveau;
        this.filtrageType = filtrageType;
        this.ordreTriage = ordreTriage;
    }
    public ArrayList<Membre> getaTrier() {
        return aTrier;
    }
    public boolean isFilterSurPaye() {
        return filterSurPaye;
    }
    public ArrayList<String> getFiltrageType() {
        return filtrageType;
    }
    public ArrayList<Integer> getFiltrageNiveau() {
        return filtrageNiveau;
    }
    public ArrayList<Integer> getOrdreTriage() {
        return ordreTriage;
    }
    @Override
    public String toString() {
        return "SvgListe [aTrier=" + aTrier + ", filterSurPaye=" + filterSurPaye
                + ", ordreTriage=" + ordreTriage + "]";
    }
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((aTrier == null) ? 0 : aTrier.hashCode());
        result = prime * result + (filterSurPaye ? 1231 : 1237);
        result = prime * result + ((filtrageType == null) ? 0 : filtrageType.hashCode());
        result = prime * result + ((filtrageNiveau == null) ? 0 : filtrageNiveau.hashCode());
        result = prime * result + ((ordreTriage == null) ? 0 : ordreTriage.hashCode());
        return result;
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        SvgListe other = (SvgListe) obj;
        if (aTrier == null) {
            if (other.aTrier != null)
                return false;
        } else if (!aTrier.equals(other.aTrier))
            return false;
        if (filterSurPaye != other.filterSurPaye)
            return false;
        if (filtrageType == null) {
            if (other.filtrageType != null)
                return false;
        } else if (!filtrageType.equals(other.filtrageType))
            return false;
        if (filtrageNiveau == null) {
            if (other.filtrageNiveau != null)
                return false;
        } else if (!filtrageNiveau.equals(other.filtrageNiveau))
            return false;
        if (ordreTriage == null) {
            if (other.ordreTriage != null)
                return false;
        } else if (!ordreTriage.equals(other.ordreTriage))
            return false;
        return true;
    }


    
    

    
}
